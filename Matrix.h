#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


typedef struct {

    int rows;
    int cols;

    int * matData; //Pointer to matrix data in memory

}matrix;


matrix * create_M(const int matArray[], int rows, int cols);
bool print_M(matrix *m1);
bool copy_M(const matrix *m1, matrix *m2);
bool destroy_M(matrix *m1);


bool arith_M(const matrix *m1, const matrix *m2, matrix *m3, char op);
bool multipl_yM(const matrix *m1, const matrix *m2, matrix *m3);
bool scale_M(const matrix *m1, matrix *m2, const int scalar);
bool diagonalise_M(const matrix *m1, matrix *m2);
bool transpose_M(matrix *m1);
bool row_reduction_M(matrix *m1);
bool inverse_M(matrix *m1);


int exponential_M(const matrix *m1);
int determinant_M(const matrix *m1);
int * eigenvalues_M(const matrix *m1);
int * eigenVectors_M(const matrix *m1);











