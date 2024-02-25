#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
int main(){
   int x=100;
   Matrix A = newMatrix(x);
   Matrix B = newMatrix(x);

   changeEntry(A, 1,2,1); changeEntry(B, 1,2,1);
   changeEntry(A, 1,0,2); changeEntry(B, 1,0,5);
   changeEntry(A, 2,1,4); changeEntry(B, 1,1,1);
   changeEntry(A, 0,2,9); changeEntry(B, 5,2,1);

   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);
   printf("\n");

   printf("%d\n", NNZ(B));
   printMatrix(stdout, B);
   printf("\n");

   Matrix C
   C = product(B, B);
   printf("%d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");

   Matrix D;
   D = sum(A, B);
   printf("%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");


   Matrix E;
   E = diff(A, A);
   printf("%d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");

   printf("%s\n", equals(A, H)?"true":"false" );


   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   return EXIT_SUCCESS;
}
