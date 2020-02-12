#include <stdlib.h>
#include <stdio.h>

typedef float Element_t;

typedef struct {
    const int column;
    const int row;
} Order_t;

typedef struct {
    const Order_t *order;
    const int is_square;
    const int num_elements;
    Element_t *elements;
} Matrix_t;

Order_t *create_order(int num_rows, int num_columns)
{
    Order_t *order = malloc(sizeof(Order_t));
    *(int *)&order->row = num_rows;
    *(int *)&order->column = num_columns;

    return order;
}

Matrix_t *create_matrix(int num_rows, int num_columns)
{
    Matrix_t *matrix = malloc(sizeof(Matrix_t));
    Order_t *order = create_order(num_rows, num_columns);

    matrix->order = (Order_t *) order;
    *(int *)&matrix->is_square = (num_columns == num_rows);
    *(int *)&matrix->num_elements = num_rows * num_columns;
    matrix->elements = (Element_t *) malloc(sizeof(Element_t) * matrix->num_elements);

    return matrix;
}

int is_same_order_matrix(Matrix_t *A, Matrix_t *B)
{
    return (A->order->column == B->order->column)
        && (A->order->row == B->order->row);
}

void check_same_order_matrix(Matrix_t *A, Matrix_t *B)
{
    if (!is_same_order_matrix(A, B)) {
        printf("%p and %p are not of the same order.\n", A, B);
        exit(-1);
    }
}

void fill_matrix(Element_t *source, Matrix_t *sink)
{
    int i, j;

    for (i=0; i<sink->order->row; i++) {
        for (j=0; j<sink->order->column; j++) {
            *(sink->elements + i*(sink->order->column) + j) = *(source + i*(sink->order->column) + j);
        }
    }
}

void print_matrix(Matrix_t *A)
{
    int i, j;

    for (i=0; i<A->order->row; i++) {
        printf("|");
        for (j=0; j<A->order->column; j++) {
            printf("%10.2f", *(A->elements + i*(A->order->column) + j));
        }
        printf(" |\n");
    }
}

Matrix_t *get_row(Matrix_t *A, int row)
{
    if (row < 1 || row > A->order->row) {
        printf("invalid row number\n");
        return NULL;
    }

    Matrix_t *output = create_matrix(1, A->order->column);

    int offset = (row-1)*(A->order->column);
    int col;

    for (col=0; col<A->order->column; col++) {
        *(output->elements + col) = *(A->elements + offset + col);
    }

    return output;
}

Matrix_t *get_column(Matrix_t *A, int column) // user input column=1,2,3 | real column = 0,1,2
{
    if (column < 1 || column > A->order->column) {
        printf("invalid column number\n");
        return NULL;
    }

    Matrix_t *output = create_matrix(A->order->row, 1);

    int offset = (column-1);
    int row;

    for (row=0; row<A->order->row; row++) {
        *(output->elements + row) = *(A->elements + offset + row*(A->order->column));
    }

    return output;
}

Matrix_t *add_matrix(Matrix_t *A, Matrix_t *B, Matrix_t *C)
{
    check_same_order_matrix(A, B);

    int i;
    for (i = 0; i<A->num_elements; i++) {
        *(C->elements + i) = *(A->elements + i) + *(B->elements + i);
    }

    return C;
}

// B = scalar * A
Matrix_t *scalar_product(Matrix_t *A, Matrix_t *B, float scalar)
{
    check_same_order_matrix(A, B);

    int i;
    for (i=0; i<A->num_elements; i++) {
        *(B->elements + i) = *(A->elements + i) * scalar;
    }

    return B;
}

// A - B = C
Matrix_t *subtract_matrix(Matrix_t *A, Matrix_t *B, Matrix_t *C)
{
    check_same_order_matrix(A, B);
    
    int i;
    for (i = 0; i<A->num_elements; i++) {
        *(C->elements + i) = *(A->elements + i) - *(B->elements + i);
    }

    return C;
}

Order_t *get_matrix_product_order(Matrix_t *A, Matrix_t *B)
{
    Order_t *order = malloc(sizeof(Order_t));
    *(int *)&order->row = A->order->row;
    *(int *)&order->column = B->order->column;

    return order;
}

Matrix_t *matrix_product(Matrix_t *A, Matrix_t *B, Matrix_t *C)
{
    if (A->order->column != B->order->row) {
        printf("Column of matrix A does not match row of matrix B");
        return C;
    }

    int rowA, colB, new_width;
    float col_value = 0.00, part_value = 0.00;

    Order_t *order = get_matrix_product_order(A, B);

    new_width = order->column;

    for (rowA = 1; rowA<=A->order->row; rowA++)
    {
        Matrix_t *row = get_row(A, rowA);
        
        for (colB = 1; colB<=B->order->column; colB++) {
            Matrix_t *column = get_column(B, colB);

            // dot product
            int i;
            for (i=0; i<row->order->column; i++) {
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

Matrix_t *transpose_matrix(Matrix_t *A, Matrix_t *AT)
{
    int old_row, old_column, new_row, new_column;

    int old_width = A->order->column;
    int new_width = A->order->row;

    for (old_row=0; old_row<A->order->row; old_row++) {
        for (old_column=0; old_column<A->order->column; old_column++) {
            
            new_row = old_column;
            new_column = old_row;

            *(AT->elements + new_row*new_width + new_column) = *(A->elements + old_row*old_width + old_column);
            
        }
    }

    return AT;
}

float det_matrix(Matrix_t *A)
{
    return 0.00;
}