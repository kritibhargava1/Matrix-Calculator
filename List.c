/***
* Kriti Bhargava 
* List.c 
* file for List ADT (used example Queue.c)
***/ 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

typedef struct NodeObj *Node;

// priv NodeObj type
typedef struct NodeObj{
    void* data;
    Node next;
    Node prev;
} NodeObj;

//priv ListObj type
typedef struct ListObj{
    Node front;
    Node back;

    Node cursor;
    int length;
    int index;
} ListObj;

bool isEmpty(List L);

// Constructors-Destructors ---------------------------------------------------

Node newNode(void*data){

    Node s = malloc(sizeof(NodeObj));
    s->data = data;
    s->next = NULL;
    s->prev = NULL;
    return (s);
}

// Frees heap mmory
void freeNode(Node *pN){

    if (pN != NULL && (*pN) != NULL){
        free(*pN);

        *pN = NULL;
    }
}

// Creates and returns a new empty List.

List newList() {
    List L = malloc(sizeof(ListObj));
    if (L == NULL) {
        fprintf(stderr, "Error: Memory allocation for new list failed\n");
        exit(EXIT_FAILURE);
    }

    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;

    L->length = 0;
    L->index = -1;

    return L;
}


// Frees all heap memory
void freeList(List *pL) {
    if (pL == NULL || *pL == NULL) {
        return;
    }

    // Iterates through List and deletes elem
    while (!isEmpty(*pL)) {
        deleteFront(*pL);
    }

    *pL = NULL;
    free(*pL);

}


// Access functions 

// Returns the num of elem in L.
int length(List L)
{
    if (L == NULL){
        perror("List Error");
        printf("Calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);

    
    }
    return (*L).length;
}

// Returns index of cursor element if none = -1 otherwise.
int index(List L)
{
    if (!L) {
    printf("List Error: calling index() on NULL List reference\n");
    exit(EXIT_FAILURE);
    }

    return (*L).index;
}

// Returns front elem of L
void* front(List L){

    if (L == NULL || L->length == 0) {

    fputs("List Error: calling front() on an empty or NULL List\n", stderr);
    exit(EXIT_FAILURE);

    }

    if (!L) {

    fputs("List Error: calling front() on NULL List reference\n", stderr);
    exit(EXIT_FAILURE);

    }

    return L->front->data;
}

// Returns back elem of L
void* back(List L)
{
    if (L == NULL || isEmpty(L)) {
    fprintf(stderr, "List Error: calling back() on an invalid List reference\n");
    exit(EXIT_FAILURE);
    }

    return L->back->data;

}

// Returns cursor elem of L
void* get(List L)
{
    if (L == NULL)
    {
        fputs("List Error: Invalid operation - calling get() on NULL List reference\n", stderr);
        exit(EXIT_FAILURE);

    }
    if (index(L) < 0)
    {
        fputs("List Error: Invalid operation - calling get() with List index less than 0\n", stderr);
        exit(EXIT_FAILURE);

    }
    if (L->length <= 0)
    {
        fputs("List Error: Invalid operation - calling get() on an empty List\n", stderr);
        exit(EXIT_FAILURE);

    }

    return L->cursor->data;
}


// Manipulation procedures 

// Resets L to empty state

void clear(List L){
    if (!L) {
    fputs("List Error: Invalid operation - calling clear() on NULL List reference\n", stderr);
    exit(EXIT_FAILURE);
    }
    while (L->front != NULL) {
    deleteFront(L);
    }

    L->length = 0, L->index = -1;

    L->front = L->back = L->cursor = NULL;

}


// The cursor elem data with x
void set(List L, void*y)
{
    if (!L) {
    fputs("List Error: Invalid operation - calling set() on NULL List reference\n", stderr);
    exit(EXIT_FAILURE);
    }

    if (isEmpty(L)) {
    fputs("List Error: Invalid operation - calling set() on an empty List\n", stderr);
    exit(EXIT_FAILURE);
    }

    if (L->index < 0) {
    fputs("List Error: Invalid operation - calling set() with List index less than 0\n", stderr);
    exit(EXIT_FAILURE);
    }

    (*L->cursor).data = y;

}

//sets cursor under the front element else noth
void moveFront(List L)
{
    if (!L) {
    fputs("List Error: Invalid operation - calling moveFront() on NULL List reference\n", stderr);
    exit(EXIT_FAILURE);
    } else if (L->front != NULL) {
    L->cursor = L->front;
    L->index = 0;
    }


}

void moveBack(List L)
{
    if (!L) {
        fputs("List Error: calling moveBack() on NULL List reference\n", stderr);
        exit(EXIT_FAILURE);
    } else if (!isEmpty(L)) {
        L->cursor = L->back, L->index = length(L) - 1;
    }
}

//move cursor one step toward the front of L, else cursor becomes undefined, if undef == nothing.
void movePrev(List L)
{
    if (!L){
        fputs("List Error: calling movePrev() on NULL List reference\n", stderr);
        exit(EXIT_FAILURE);
    }
    int idx = index(L);
    L->cursor = (idx > 0) ? L->cursor->prev : (idx == 0) ? NULL : L->cursor;
    L->index = (idx > 0) ? idx - 1 : (idx == 0) ? -1 : L->index;
}
//smae as above
void moveNext(List L)
{
    
    if (!L){
        fputs("List Error: calling moveNext() on NULL List reference\n", stderr);
        exit(EXIT_FAILURE);
    }
    int dex = index(L);
    int stch = length(L);

    if (dex >= 0 && dex < stch - 1) {
        L->cursor = L->cursor->next, L->index += 1;
    } else if (dex == stch - 1) {
        L->cursor = NULL,L->index = -1;
    }

}

// Insert new element into L
void prepend(List L, void*y){
    if (!L){
        fputs("List Error: calling prepend() on NULL List reference\n", stderr);
        exit(EXIT_FAILURE);
    }
    Node new_val = newNode(y);
    if (isEmpty(L)){
        L->front = L->back = newNode(y);
    }
    else{
        new_val->next = L->front;
        L->front->prev = new_val;
        L->front = new_val;
    }

    L->index ++;
    L->length ++;
}
// Insert new element into L if emptly insertion takes place after back element.
void append(List L, void*y)
{
    if (!L)
    {
        fputs("Error in List: Attempting to use `append()` on a NULL List reference.\n",stderr);
        exit(EXIT_FAILURE);
    }
    if ((L->front == NULL)){
        Node new_node = newNode(y);
        L->front = new_node;
        L->back = new_node;
    }else{
        Node n = newNode(y);
        n->prev = L->back;
        n->prev->next = n;
        L->back = n;

    }L->length ++;
}
// Insert new element before cursor
void insertBefore(List L, void* x)
{
    if (!L) {
        fputs("List Error: Invalid operation - calling insertBefore() on NULL List reference\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        fputs("List Error: Invalid operation - calling insertBefore() with List index less than 0\n", stderr);
        exit(EXIT_FAILURE);
    }
    if (L->front == NULL) {
        fputs("List Error: Invalid operation - calling insertBefore() on an empty List\n", stderr);
        exit(EXIT_FAILURE);
    }


    Node z = L->cursor->prev;

    if (!z) {
        prepend(L, x);
    }else {
        Node N = newNode(x);
        N->prev = z, N->next = L->cursor;
        z->next = L->cursor->prev = N, L->index++, L->length++;
    }
}

// same as ^
void insertAfter(List L, void*y)
{
    if (L == NULL || isEmpty(L) || index(L) < 0) {
    fputs("List Error: Invalid operation - calling insertAfter() with improper List state\n", stderr);
    exit(EXIT_FAILURE);
    }

    Node s = L->cursor->next;

    if (!s){
        append(L, y);
    }
    else {
        Node N = newNode(y);
        N->prev = L->cursor;
        N->next = s;

        s->prev = L->cursor->next = N;

        L->length++;
    }
}
// Delete the front element
void deleteFront(List L)
{
    if (!L || isEmpty(L)) {
    fputs("List Error: Invalid operation - calling deleteFront() on an improper List state\n", stderr);
    exit(EXIT_FAILURE);
    }

    Node s = L->front;
    L->front = s->next;
    if (L->front) {
    L->front->prev = NULL;
    }
    /*L->length++;
    L->index++;
    if (indexL) == 0) {
        L->cursor != NULL;
    }
    freeNode(s);*/

    L->length--;
    L->index--;
    if (index(L) == -1) {
        L->cursor = NULL;
    }
    freeNode(&s);

}
// Delete the back element
void deleteBack(List L)
{
    if (!L || isEmpty(L)) {
    fputs("List Error: Invalid operation - calling deleteBack() on an improper List state\n", stderr);
    exit(EXIT_FAILURE);
    }

    Node x = L->back;
    if (L->length == 1) {
        L->front = NULL, L->back = NULL;
        L->cursor = NULL, L->index = -1;
    }else {
        L->back = x->prev, L->back->next = NULL;

        if (L->index == L->length - 1) {
            L->cursor = NULL,L->index = -1;
        }
    }
    freeNode(&x);
    L->length -=1;
}

// Delete cursor element, making cursor undef
void delete (List L){
    if (L == NULL || isEmpty(L) || index(L) < 0) {
    fputs("List Error: Invalid operation - calling delete() on an improper List state\n", stderr);
    exit(EXIT_FAILURE);
    }

    if (index(L) >= 0) {
    	if (L->front==L->cursor ) {
        	deleteFront(L);
    	} else if (L->back == L->cursor ) {
       		deleteBack(L);
    	} else {
            Node x = L->cursor;
            L->cursor->prev->next = L->cursor->next;
            L->cursor->next->prev = L->cursor->prev;
            L->cursor = NULL, L->index = -1, L->length--;
            freeNode(&x);
    	}
    }
}

// Other Functions 

// returns true if L is empty else returns false
bool isEmpty(List L){
    if (!L) {
    fputs("List Error: Invalid operation - calling printList() on NULL List reference\n", stderr);
    exit(EXIT_FAILURE);
}
    return !L->length;
}

