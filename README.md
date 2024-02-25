# Sparse Matrix Calculator

Welcome to the Sparse Matrix Calculator project. This project focuses on implementing efficient algorithms for performing matrix operations on sparse matrices. 

## Overview

This project creates a program in C capable of performing various matrix operations on sparse matrices efficiently. The main operations include matrix addition, subtraction, multiplication, scalar multiplication, and transposition. The program will read input matrices from files, perform the specified operations, and write the results to an output file.

## Files Included

- **Sparse.c**: Main program handling input and output files, and acting as a client of the Matrix ADT.
- **Matrix.c**: Implementation of the Matrix ADT containing functions for matrix operations.
- **Matrix.h**: Header file for the Matrix ADT containing function declarations.
- **MatrixTest.c**: Client module to test the Matrix ADT in isolation.
- **List.c**: Implementation of the modified List ADT used within the Matrix ADT.
- **List.h**: Header file for the modified List ADT containing function declarations.
- **ListTest.c**: Client module to test the modified List ADT in isolation.
- **README.md**: This file, providing an overview of the project and instructions.
- **Makefile**: Script to compile the project and create an executable file named "Sparse".

## Functionality

The Sparse Matrix Calculator performs the following operations efficiently:
- Matrix addition
- Matrix subtraction
- Scalar multiplication
- Matrix transposition
- Matrix multiplication
- Printing matrices in specified format

## How to Use

1. Compile the project using the provided Makefile.
2. Run the executable file "Sparse" with two command line arguments: input file name and output file name.
3. Input file format: Follow the specified format for input matrices.
4. Output file: The program will write the results of matrix operations to this file.

## Testing

- Test the List and Matrix ADTs separately using ListTest.c and MatrixTest.c.
- Use provided input/output files for additional testing.


If you have any questions, feel free to reach out.
