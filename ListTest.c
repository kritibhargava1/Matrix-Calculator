/***
* Kriti Bhargava 
* krbharga 
* 2024 Winter CSE101 PA{4}
* ListTest.c 
* Test file
***/ 
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]) {
   
    // Test Lists A, B, and C
    List x = newList();
    List y = newList();
    List z = newList();
    int i;

    // Populate Lists A and B
    append(x, 6);
    append(x, 2);

    // Test equals function
    printf("Is List x equal to List y? %s\n", equals(x, y) ? "true" : "false");
   
    // Test insertion and deletion
    moveFront(x);
    for(i = 0; i < 2; i++) moveNext(x);
    

    // Clean up
    freeList(&x);


    return 0;
}

