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

typedef struct {
    int column;
    int row;
} Order_t;

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

Matrix *get_row(Matrix *A, int row)
{
    if (row < 1 || row > A->num_rows) {
        printf("row must not be bigger than matrix height.\n");
        return NULL;
    }

    Matrix *output = create_matrix(1, A->num_columns);

    int offset = (row-1)*(A->num_columns);
    int col;

    for (col=0; col<A->num_columns; col++) {
        *(output->elements + col) = *(A->elements + offset + col);
    }

    return output;
}

Matrix *get_column(Matrix *A, int column) // user input column=1,2,3 | real column = 0,1,2
{
    if (column < 1 || column > A->num_columns) {
        printf("column must not be bigger than matrix width.\n");
        return NULL;
    }

    Matrix *output = create_matrix(A->num_rows, 1);

    int offset = (column-1);
    int row;

    for (row=0; row<A->num_rows; row++) {
        *(output->elements + row) = *(A->elements + offset + row*(A->num_columns));
    }

    return output;
}

Matrix *add_matrix(Matrix *A, Matrix *B, Matrix *C)
{
    check_same_order_matrix(A, B);

    int total_elements = A->num_columns * A->num_rows;
    int i;

    for (i = 0; i<total_elements; i++) {
        *(C->elements + i) = *(A->elements + i) + *(B->elements + i);
    }

    return C;
}

// B = scalar * A
Matrix *scalar_product(Matrix *A, Matrix *B, float scalar)
{
    check_same_order_matrix(A, B);

    int total_elements = A->num_columns * A->num_rows;

    int i;
    for (i=0; i<total_elements; i++) {
        *(B->elements + i) = *(A->elements + i) * scalar;
    }

    return B;
}

Matrix *subtract_matrix(Matrix *A, Matrix *B, Matrix *C)
{
    check_same_order_matrix(A, B);

    Matrix *negativeB = create_matrix(A->num_rows, A->num_columns);

    scalar_product(B, negativeB, -1);

    add_matrix(A, negativeB, C);

    free(negativeB);

    return C;
}

Order_t *get_matrix_product_order(Matrix *A, Matrix *B)
{
    Order_t *order = malloc(sizeof(Order_t));
    order->row = A->num_rows;
    order->column = B->num_columns;

    return order;
}

Matrix *matrix_product(Matrix *A, Matrix *B, Matrix *C)
{
    if (A->num_columns != B->num_rows) {
        printf("Column of matrix A does not match row of matrix B");
        return C;
    }

    int rowA, colB, new_width;
    float col_value = 0.00, part_value = 0.00;

    Order_t *order = get_matrix_product_order(A, B);

    new_width = order->column;

    for (rowA = 1; rowA<=A->num_rows; rowA++)
    {
        Matrix *row = create_matrix(1, A->num_columns);
        row = get_row(A, rowA);
        
        for (colB = 1; colB<=B->num_columns; colB++) {
            Matrix *column = create_matrix(B->num_rows, 1);
            column = get_column(B, colB);

            // dot product
            int i;
            for (i=0; i<row->num_columns; i++) {
                part_value = *(row->elements + i) * *(column->elements + i);
                col_value += part_value;
            }

            // store the dot product value
            *(C->elements + (rowA-1)*(new_width) + (colB-1)) = col_value;

            col_value = 0.00;
            part_value = 0.00;
        }
    }

    return C;
}

Matrix *transpose_matrix(Matrix *A, Matrix *AT)
{
    int old_row, old_column, new_row, new_column;

    int old_width = A->num_columns;
    int new_width = A->num_rows;

    for (old_row=0; old_row<A->num_rows; old_row++) {
        for (old_column=0; old_column<A->num_columns; old_column++) {
            
            new_row = old_column;
            new_column = old_row;

            *(AT->elements + new_row*new_width + new_column) = *(A->elements + old_row*old_width + old_column);
            
        }
    }

    return AT;
}

float det_matrix(Matrix *A)
{
    return 0.00;
}

int main()
{
    // 4*3
    Element list[] = {
        1,2,3,
        4,5,6,
        7,8,9,
        10,11,12
    };

    // 3x3
    Element list1[] = {
        0,1,2,
        3,4,5,
        6,7,8
    };

    Matrix *A = create_matrix(4, 3);
    Matrix *B = create_matrix(3, 3);

    fill_matrix(list, A);
    fill_matrix(list1, B);

    Matrix *row = get_row(A, 4);
    Matrix *col = get_column(A, 3);

    // print_matrix(row);

    // print_matrix(col);

    Order_t *order = get_matrix_product_order(A, B);
    Matrix *output = create_matrix(order->row, order->column);

    // output->num_rows = 100;

    // scalar_product(A, output, 2);

    matrix_product(A, B, output);

    print_matrix(output);

    // Matrix *column = get_column(A, 2);

    // print_matrix(column);

    // Matrix *row = get_row(A, 2);

    // print_matrix(row);

    // print_matrix(col);

    // fill_matrix(list1, B);

    // Matrix *C = create_matrix(2,2);

    
    return 0;
}