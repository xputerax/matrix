#include <stdlib.h>
#include <stdio.h>

// #ifndef MATRIX_H
// #define MATRIX_H 1
// #endif

// typedef struct {
//     float value;
// } Element;

typedef float Element;

// typedef struct {
//     int num_elements;
//     float *elements;
// } Row;

// typedef struct {
//     int num_elements;
//     float *elements;
// } Column;

typedef struct {
    const int num_rows;
    const int num_columns;
    const int is_square;
    float *elements;
    // Row *rows;
} Matrix;

// int num_rows(Matrix *A)
// {
//     return *A->num_rows;
// }

Matrix *create_matrix(int num_rows, int num_columns)
{
    Matrix *A = malloc(sizeof(Element) * num_columns * num_rows);

    // *A = (Matrix) { .num_columns = num_columns, .num_rows = num_rows, .is_square = (num_columns == num_rows) };

    *(int *)&A->num_rows = num_rows;
    *(int *)&A->num_columns = num_columns;
    *(int *)&A->is_square = (num_columns == num_columns);

    A->elements = malloc(sizeof(Element) * num_rows * num_columns);

    return A;
}

int is_same_order_matrix(Matrix *A, Matrix *B)
{
    return (A->num_columns == B->num_columns)
        && (A->num_rows == B->num_rows);
}

void check_same_order_matrix(Matrix *A, Matrix *B)
{
    if (!is_same_order_matrix(A, B)) {
        printf("%p and %p are not of the same order.\n", A, B);
        exit(-1);
    }
}

void fill_matrix(Element *source, Matrix *sink)
{
    // check_same_order_matrix(source, sink);

    int i, j;

    for (i=0; i<sink->num_rows; i++) {
        for (j=0; j<sink->num_columns; j++) {
            *(sink->elements + i*(sink->num_columns) + j) = *(source + i*(sink->num_columns) + j);
        }
    }
}

void print_matrix(Matrix *A)
{
    int i, j;

    for (i=0; i<A->num_rows; i++) {
        printf("|");
        for (j=0; j<A->num_columns; j++) {
            printf("%5.2f", *(A->elements + i*(A->num_columns) + j));
        }
        printf(" |\n");
    }
}

Matrix *add_matrix(Matrix *A, Matrix *B, Matrix *C)
{
    check_same_order_matrix(A, B);

    int i, j;
    // Element *a = A->elements[0];
    // Element, *b = A->elements[0];

    for (i=0; i<A->num_rows; i++) {
        for (j=0; j<A->num_columns; j++) {
            *(C->elements + i*(A->num_columns) + j) = *(A->elements + i*(A->num_columns) + j) + *(B->elements + i*(A->num_columns) + j);
        }
    }

    return C;
}

Matrix *subtract_matrix(Matrix *A, Matrix *B, Matrix *C)
{
    check_same_order_matrix(A, B);

    return C;
}

Matrix *scalar_product(Matrix *A, Matrix *B, float scalar)
{
    check_same_order_matrix(A, B);

    return B;
}

Matrix *matrix_product(Matrix *A, Matrix *B, Matrix *C)
{
    // Matrix *C;
    // int C_row, C_column;

    // if (A->num_columns != B->num_rows) {
    //     printf("Column of matrix A does not match row of matrix B");
    //     return C;
    // }

    // C_row = A->num_rows;
    // C_column = B->num_columns;

    // C = create_matrix(C_row, C_column);    

    return C;
}

Matrix *transpose_matrix(Matrix *A, Matrix *AT)
{
    return AT;
}

float det_matrix(Matrix *A)
{
    return 0.00;
}

int main()
{

    Element list[4] = {1,2,3,4};
    Matrix *A = create_matrix(2, 2);

    fill_matrix(list, A);

    print_matrix(A);

    return 0;    

}