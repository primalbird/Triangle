#include <stdio.h>
#include "triangle.h"

int main() {
    printf("Hello, World!\n");
    Triangle *triangle;
    rc_triangle rc;
    rc = init_3_sides_triangle(&triangle, 3, 4, 5);
    double value = -2;
    rc = get_perimeter_triangle(triangle, &value);
    printf("perimeter = %.3f\n", value);
    rc = get_angle_triangle(triangle, alpha_triangle, &value);
    printf("alpha = %.3f\n", value);
    rc = get_angle_triangle(triangle, beta_triangle, &value);
    printf("beta = %.3f\n", value);
    rc = get_angle_triangle(triangle, gamma_triangle, &value);
    printf("gamma = %.3f\n", value);
    rc = get_square_triangle(triangle, &value);
    printf("square = %.3f\n", value);

    destroy_triangle(&triangle);
    return 0;
}
