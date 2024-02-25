/***
 * Kriti Bhargava 
 * Sparce.c 
 * This program reads input from two files specified as command-line arguments, performs various matrix operations on the input matrices, and writes the results to an output file. 
 * It defines functions to clean up resources and load matrices from files. 
 * The main function initializes matrices A and B, loads data from the input files into these matrices, performs matrix operations, prints the results to the output file, and cleans up resources.
***/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "Matrix.h"
#define MAX_LEN 100

// Function to clean up resources
void cleanUp(Matrix *A, Matrix *B, FILE *in, FILE *out) {
    freeMatrix(A);
    freeMatrix(B);
    fclose(in);
    fclose(out);
}

// Function to load matrix from file
void loadFromFile(FILE *in, char *line, char *token, Matrix M, int count_nnz) {
    double x;
    int row;
    int column;
    int j;
    row = -1;
    column = -1;

    j = 2;
    while (j - 2 <= count_nnz) {
        fgets(line, MAX_LEN, in);
        if (1 == strlen(line)) {
            j++;
            continue;
        }
        token = strtok(line, " ");
        while (NULL != token) {
            if (row == -1) {
                row = atoi(token);
            } else if (-1 == column) {
                column = atoi(token);
            } else {
                x = atoi(token);
            }
            token = strtok(NULL, " ");
        }

        changeEntry(M, row, column, x);
        row = -1;
        column = -1;
        j++;
    }
}

int main(int argc, char *argv[]){
    FILE *in, *out;
    char line[MAX_LEN];
    int x = -1, s = -1, z = -1;

    if (argc != 3 || (in = fopen(argv[1], "r")) == NULL || (out = fopen(argv[2], "w")) == NULL) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        if (in == NULL || out == NULL) {
            if (in == NULL)
                fprintf(stderr, "Not able to open file '%s' for reading\n", argv[1]);
            if (out == NULL)
                fprintf(stderr, "Not able to open file '%s' for writing\n", argv[2]);
            exit(EXIT_FAILURE);
        }
    }

    fgets(line, MAX_LEN, in);
    char *token = strtok(line, " ");

    while (NULL != token) {
        if (x == -1) x = atoi(token);
        else if (-1 == s) s = atoi(token);
        else z = atoi(token);
        token = strtok(NULL, " ");
    }

    Matrix solution;
    Matrix A = newMatrix(x);
    Matrix B = newMatrix(x);
    loadFromFile(in, line, token, A, s);
    loadFromFile(in, line, token, B, z);
    
    // Print number of non-zero entries for A and B
    fprintf(out, "A has %d non-zero entries:\n", s);
    printMatrix(out, A);
    fprintf(out, "\n");
    fprintf(out, "B has %d non-zero entries:\n", z);
    printMatrix(out, B);
    fprintf(out, "\n");

    // Perform matrix operations and print results
    fprintf(out, "(1.5)*A =\n");
    solution = scalarMult(1.5, A);
    printMatrix(out, solution);
    fprintf(out, "\n");
    freeMatrix(&solution);

    fprintf(out, "A+B =\n");
    solution = sum(A, B);
    printMatrix(out, solution);
    fprintf(out, "\n");
    freeMatrix(&solution);

    fprintf(out, "A+A =\n");
    solution = sum(A, A);
    printMatrix(out, solution);
    fprintf(out, "\n");
    freeMatrix(&solution);

    fprintf(out, "B-A =\n");
    solution = diff(B, A);
    printMatrix(out, solution);
    fprintf(out, "\n");
    freeMatrix(&solution);

    fprintf(out, "A-A =\n");
    solution = diff(A, A);
    printMatrix(out, solution);
    fprintf(out, "\n");
    freeMatrix(&solution);

    fprintf(out, "Transpose(A) =\n");
    solution = transpose(A);
    printMatrix(out, solution);
    fprintf(out, "\n");
    freeMatrix(&solution);

    fprintf(out, "A*B =\n");
    solution = product(A, B);
    printMatrix(out, solution);
    fprintf(out, "\n");
    freeMatrix(&solution);

    fprintf(out, "B*B =\n");
    solution = product(B, B);
    printMatrix(out, solution);
    fprintf(out, "\n");
    freeMatrix(&solution);

    cleanUp(&A, &B, in, out);
    return 0;
}
