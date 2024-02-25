/***
* Kriti Bhargava 
* Matrix.c
* implements basic matrix operations in C, including addition, subtraction, multiplication, and transposition
***/ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Matrix.h"

typedef struct EntryObj *Entry;

typedef struct EntryObj{
    int col;double val;
} EntryObj;

typedef struct MatrixObj{
    int tiers;int count_NNZ;List *entries;
} MatrixObj;

// enums

typedef enum{
    ADDITION,SUBTRACTION,
} OP_t;



// Calculates the dot product of two lists
double calculateDotProduct(List P, List Q);

// Inserts an entry into a list in a sorted order
void insertSorted(List L, Entry X);

// Helper function for matrix addition or subtraction
Matrix sumOrDiffHelper(Matrix A, Matrix B, OP_t operation);
// Constructors-Destructors 

// Creates a new entry with given column and value
Entry createEntry(int col, double val){
    Entry newEntry = malloc(sizeof(EntryObj));
    newEntry->col = col;
    newEntry->val = val;
    return newEntry;
}

// Frees the memory allocated to an entry
void access(Entry *pE){
    if (pE != NULL) {
        if (*pE != NULL) {
            free(*pE);
            *pE = NULL;
        }
}
}

// Creates a new matrix with given size
Matrix newMatrix(int n)
{
    Matrix x = malloc(sizeof(*x));
    if (x != NULL) {
        x->tiers = n;
        x->count_NNZ = 0;
        x->entries = malloc(sizeof(List) * (n + 1));
        if (x->entries == NULL) {
            free(x);
            x = NULL;
        }
    }

    int i = 0;
    while (i < n) {
        x->entries[i + 1] = newList();
        i++;
    }


    return x;
}

// Frees the memory allocated to a matrix
void freeMatrix(Matrix *pM)
{
    if (*pM != NULL && pM != NULL) {
        Matrix x = *pM;
        Entry entry;
        List tier;

        int i = 1;
        while (i <= x->tiers) {
            if ((tier = x->entries[i]) != NULL) {
                moveFront(tier);
                while (moveNext(tier), index(tier) >= 0) {
                    entry = get(tier);
                    access(&entry);
                }
                freeList(x->entries + i);

            }
            i++;
        }

        free(x->entries), x->entries = NULL;
        free(*pM), *pM = NULL;

    }
}

// Access functions

// Returns the number of tiers in a matrix
int size(Matrix M){

    if (!M) {
    fputs("Matrix Error: calling a size() on NULL Matrix reference\n", stderr);
    exit(EXIT_FAILURE);
    }


    return (*M).tiers;

}

// Returns the number of non-zero elements in a matrix
int NNZ(Matrix M){
    if (!M) {
    fputs("Matrix Error: calling NNZ() on NULL Matrix reference\n", stderr);
    exit(EXIT_FAILURE);
    }

    return M->count_NNZ;

}

int equals(Matrix A, Matrix B) {
    if (!A || !B) {
        fputs("Matrix Error: calling equals() on NULL Matrix reference\n", stderr);
        return 0;
    }

    if (A->count_NNZ != B->count_NNZ || A->tiers != B->tiers) {
        return 0;
    }

    for (int i = 1; i <= A->tiers; i++) {
        List num1 = A->entries[i];
        List num2 = B->entries[i];

        moveFront(num1);
        moveFront(num2);

        while (index(num1) >= 0 && index(num2) >= 0) {
            Entry val1 = (Entry)get(num1);
            Entry val2 = (Entry)get(num2);

            if (val1->col != val2->col || val1->val != val2->val) {
                return 0;
            }

            moveNext(num1);
            moveNext(num2);
        }

        // If both lists are exhausted, continue to the next tier
        if (index(num1) < 0 && index(num2) < 0) {
            continue;
        } else { // One list has elements while the other is exhausted
            return 0;
        }
    }

    return 1;
}

// Manipulation prscedures
// Sets all elements of a matrix to zero

void makeZero(Matrix M){
    Entry entry;

    if (!M) {
        fputs("Matrix Error: calling an makeZero() on NULL Matrix reference\n", stderr);
        exit(EXIT_FAILURE);
    }

    int i = 1;
    while (i <= M->tiers){
        List tier = M->entries[i];
        if (NULL != tier){
            moveFront(tier);
            while (0 < index(tier)){
                entry = get(tier);
                access(&entry);
                moveNext(tier);
            }
        }
        clear(M->entries[i]);
        
        i++;
    }


    M->count_NNZ = 0;
}

// Changes the value of an element in the matrix

void changeEntry(Matrix M, int i, int j, double x){
    List tier = M->entries[i];
    Entry entry;
    moveFront(tier);

    if (M == NULL || i < 1 || j < 1 || i > size(M) || j > size(M)) {
    fprintf(stderr, "Matrix Error: calling changeEntry() with invalid parameters\n");
    exit(EXIT_FAILURE);
    }

    while (0 < index(tier)){
        entry = (Entry)get(tier);
        if (x != 0.0 && entry->col == j) {
            entry->val = x;
        } else if (entry->col == j) {
            access(&entry);
            delete (M->entries[i]);
            M->count_NNZ--;
            return;
        }

        moveNext(tier);
    }

    if (x != 0.0) {
        Entry newEntry = createEntry(j, x);
        if (newEntry != NULL) {
            insertSorted(M->entries[i], newEntry);
            M->count_NNZ++;
        }
}
}

// Matrix Aritmetic operations
// Creates a copy of a matrix
Matrix copy(Matrix A){
    Matrix dupe1 = newMatrix(size(A));
    if (!A) {
        fputs("Matrix Error: calling copy() on NULL Matrix reference\n", stderr);
        exit(EXIT_FAILURE);
    }
    int i = 1;
    while (i <= dupe1->tiers) {
        List tier = A->entries[i];
        moveFront(tier);
        while (index(tier) >= 0) {
            Entry entry = get(tier);
            changeEntry(dupe1, entry->col, i ,entry->val);
            moveNext(tier);
        }
        i++;
    }
    return dupe1;
}

// Transposes a matrix
Matrix transpose(Matrix A){
    if (!A) {
        fputs("Matrix Error: calling transpose() on NULL Matrix reference\n", stderr);
        exit(EXIT_FAILURE);
    }
    
    Matrix transposeMatrix = newMatrix(size(A));

    int i = 1;
    while (i <= size(A)) {
        List tier = A->entries[i];
        moveFront(tier);

        while (index(tier) >= 0) {
            Entry entry = get(tier);
            changeEntry(transposeMatrix, entry->col, i, entry->val);
            moveNext(tier);
        }
        
        i++;
    }


    return transposeMatrix;
}

// Multiplies a matrix by a scalar
Matrix scalarMult(double x, Matrix A){
    Matrix scalar_M = newMatrix(size(A));
    if (!A) {
        fputs("Matrix Error: calling scalarMult() on NULL Matrix reference\n", stderr);
        exit(EXIT_FAILURE);
    }

    int i = 1;
    while (i <= size(A)) {
        List tier = A->entries[i];
        moveFront(tier);

        while (index(tier) >= 0) {
            Entry entry = get(tier);
            changeEntry(scalar_M, i, entry->col,x* entry->val);
            moveNext(tier);
        }
        
        i++;
    }

    return scalar_M;
}

// Adds two matrices
Matrix sum(Matrix A, Matrix B){
    if (A == NULL || B == NULL || size(A) != size(B)) {
        fprintf(stderr, "Matrix Error: ");
        if (A == NULL || B == NULL) {
            fputs("calling sum() on NULL Matrix reference\n", stderr);
        } else {
            fputs("calling sum() on size(A) != size(B)\n", stderr);
        }
        exit(EXIT_FAILURE);
    }

    return sumOrDiffHelper(A, B, ADDITION);
}

// Subtracts one matrix from another
Matrix diff(Matrix A, Matrix B)
{
    if (A == NULL || B == NULL || size(A) != size(B)) {
        fprintf(stderr, "Matrix Error: ");
        if (A == NULL || B == NULL) {
            fputs("calling sum() on NULL Matrix reference\n", stderr);
        } else {
            fputs("calling sum() on size(A) != size(B)\n", stderr);
        }
        exit(EXIT_FAILURE);
    }
    return sumOrDiffHelper(A, B, SUBTRACTION);
}


// Multiplies two matrices
Matrix product(Matrix A, Matrix B){
    
    Matrix ans = newMatrix(size(A));
    Matrix shift1 = transpose(B);

    if (A == NULL || B == NULL || size(A) != size(B)) {
        fprintf(stderr, "Matrix Error: ");
        if (A == NULL || B == NULL) {
            fputs("calling sum() on NULL Matrix reference\n", stderr);
        } else {
            fputs("calling sum() on size(A) != size(B)\n", stderr);
        }
        exit(EXIT_FAILURE);
    }

    int i = 1;
    while (i <= size(A)) {
        List num1 = A->entries[i];
        int j = 1;
        while (j <= size(A)) {
            List num2 = shift1->entries[j];
            changeEntry(ans, i, j, calculateDotProduct(num1, num2));
            j++;
        }
        i++;
    }
    freeMatrix(&shift1);

    return ans;
}

// Other Functions
// Prints the matrix to a file

void printMatrix(FILE *out, Matrix M){

    if (!M) {
        fputs("Matrix Error: attempting to print a NULL Matrix reference\n", stderr);
        exit(EXIT_FAILURE);
    }

    int i = 1;
    while (i <= size(M)) {
        List tier = M->entries[i];
        if (length(tier) > 0) {
            fprintf(out, "%d: ", i);
            for (moveFront(tier); index(tier) >= 0; moveNext(tier)) {
                Entry entry = get(tier);
                fprintf(out, "(%d, %.1f) ", entry->col, entry->val);
            }
            fprintf(out, "\n");
        }
        i++;
    }

}

// Helper Functions -----------------------------------------------------------

// Calculates the dot product of two lists
double calculateDotProduct(List P, List Q) {
    double answer = 0;

    moveFront(P);
    moveFront(Q);

    if (P == NULL || Q == NULL) {
        fprintf(stderr, "Matrix Error: calling calculateDotProduct() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }


    while (index(Q) >= 0 && index(P) >= 0 ) {
        Entry entryP = get(P);
        Entry entryQ = get(Q);

        if (entryQ->col == entryP->col) {
            answer = answer + (entryP->val * entryQ->val);
            moveNext(P);
            moveNext(Q);
        } 
        else {
            if (entryQ->col < entryP->col) 
                moveNext(Q);
            else 
                moveNext(P);
        }

    }

    return answer;
}
// Inserts an entry into a list in a sorted order
void insertSorted(List L, Entry X){
    if (!L) {
        fputs("Matrix Error: inserting into a NULL List reference\n", stderr);
        exit(EXIT_FAILURE);
    }

    int size = length(L);

    if (size == 0){
        append(L, X);
    }else{
        moveFront(L);
        if ((size > index(L) && index(L) >= 0) || size == length(L)) {
            Entry entry = (Entry)get(L);
            if ((size > index(L) && index(L) >= 0) && X->col < entry->col) {
                insertBefore(L, X);
                return;
            } else if (size == length(L)) {
                append(L, X);
            }
        }

    }
}

// Helper function for matrix addition or subtraction
Matrix sumOrDiffHelper(Matrix A, Matrix B, OP_t operation) {
    int s = SUBTRACTION == operation;
    int k = size(A);
    Matrix answer;
    int t = operation == ADDITION;
    Entry val1, val2;
    double x;
    int i = 1;

    if (B == A) {
        answer = (t) ? scalarMult(2, A) : newMatrix(k);
    }else {
        answer = newMatrix(k);

        while (i <= k) {
            List num2 = B->entries[i];
            List num1 = A->entries[i];
            moveFront(num2);
            moveFront(num1);

            while (index(num1) >= 0 || index(num2) >= 0) {
                if (index(num2) >= 0 && index(num1) >= 0) {
                    Entry val1 = get(num1);
                    Entry val2 = get(num2);

                    if (val1->col == val2->col) {
                        x = (t) ? (val1->val + val2->val) : (val1->val - val2->val);
                        changeEntry(answer, i, val1->col, x);
                        moveNext(num1);
                        moveNext(num2);
                        continue;
                    }

                    if (val1->col > val2->col) {
                        x = val2->val;
                        if (s) {
                            x = -x;
                        }
                        changeEntry(answer, i, val2->col, x);
                        moveNext(num2);
                        continue;
                    }

                    if (val1->col < val2->col) {
                        changeEntry(answer, i, val1->col, val1->val);
                        moveNext(num1);
                        continue;
                    }
                }

                while (index(num1) >= 0 || index(num2) >= 0) {
                    if (index(num1) >= 0) {
                        val1 = get(num1);
                        changeEntry(answer, i, val1->col, val1->val);
                        moveNext(num1);
                    }
                    
                    if (index(num2) >= 0) {
                        val2 = get(num2);
                        x = val2->val;
                        if (s){
                            x = -x;
                        }
                        changeEntry(answer, i, val2->col, x);
                        moveNext(num2);
                    }
                }
            }

            i++;
        }

    }

    return answer;
}
