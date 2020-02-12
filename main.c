#include "matrix.h"

int main(void)
{
    // 4*3
    Element_t list[] = {
        1,2,3,
        4,5,6,
        7,8,9,
        10,11,12
    };

    // 3x3
    Element_t list1[] = {
        0,1,2,
        3,4,5,
        6,7,8
    };

    Matrix_t *A = (Matrix_t *) create_matrix(4,3);
    Matrix_t *B = (Matrix_t *) create_matrix(3,3);

    fill_matrix(list, A);
    fill_matrix(list1, B);

    Order_t *order = get_matrix_product_order(A, B);
    Matrix_t *output = create_matrix(order->row, order->column);

    matrix_product(A, B, output);
    print_matrix(output);

    return 0;
}