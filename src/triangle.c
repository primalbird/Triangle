#include "triangle.h"

#include <assert.h>
#include <malloc.h>
#include <math.h>

#undef EPSILON
#define EPSILON 10e-6

#define check_setter_arguments(triangle_ptr, value)                             \
    if (!(triangle_ptr))                                                        \
        return TRIANGLE_IS_NULL;                                                \
    if (!isfinite(value))                                                       \
        return IS_NOT_FINITE_ARGUMENT;                                          \
    if (!is_greater_d(value, 0))                                                \
        return INCORRECT_ARGUMENT;

#define check_getter_ptr(triangle_ptr, value_ptr)                               \
    if (!(triangle_ptr))                                                        \
        return TRIANGLE_IS_NULL;                                                \
    if (!(value_ptr))                                                           \
        return ARGUMENT_IS_NULL;

#define check_init_values(a, b, c)                                              \
    if (!(isfinite(a) && isfinite(b) && isfinite(c)))                           \
        return IS_NOT_FINITE_ARGUMENT;                                          \
    if (!(is_greater_d(a, 0) && is_greater_d(b, 0) && is_greater_d(c, 0)))      \
        return INCORRECT_ARGUMENT;

#define malloc_triangle()                                                       \
    malloc(sizeof(Triangle));                                                   \
    if (!triangle_ptr)                                                          \
        return MEMORY_ALLOCATION_ERROR;

struct Triangle {
    double a;
    double b;
    double c;
    double alpha;
    double beta;
    double gamma;
};

/**
 * Constructors
 */
rc_triangle init_3_sides_triangle(Triangle **triangle, double a, double b, double c)
{
    check_init_values(a, b, c)
    if (!check_ineq_(a, b, c))
        return INCORRECT_ARGUMENT;
    Triangle *triangle_ptr = malloc_triangle()
    set_sides_triangle_(triangle_ptr, a, b, c);
    calc_angles(triangle_ptr);
    *triangle = triangle_ptr;
    return OK;
}

rc_triangle init_2_sides_1_angle_triangle(Triangle **triangle, double a, double b, double gamma)
{
    check_init_values(a, b, gamma)
    if (!(is_below_d(gamma, M_PI)))
        return INCORRECT_ARGUMENT;
    Triangle *triangle_ptr = malloc_triangle()
    set_sides_triangle_(triangle_ptr, a, b, sqrt((a * a) + (b * b) - (2 * a * b * cos(gamma))));
    calc_angles(triangle_ptr);
    *triangle = triangle_ptr;
    return OK;
}

rc_triangle init_1_side_2_angles_triangle(Triangle **triangle, double a, double beta, double gamma)
{
    check_init_values(a, beta, gamma)
    if (!(is_below_d(beta + gamma, M_PI)))
        return INCORRECT_ARGUMENT;
    Triangle *triangle_ptr = malloc_triangle()
    triangle_ptr->alpha = M_PI - (beta + gamma);
    triangle_ptr->beta  = beta;
    triangle_ptr->gamma = gamma;
    set_sides_triangle_(triangle_ptr, a, a * sin(beta)  / sin(triangle_ptr->alpha),
                                        a * sin(gamma)  / sin(triangle_ptr->alpha));
    *triangle = triangle_ptr;
    return OK;
}

/**
 * Destructor
 */
rc_triangle destroy_triangle(Triangle **triangle)
{
    free(*triangle);
    *triangle = NULL;
    return OK;
}

/**
 * Getters
 */
inline rc_triangle get_side_triangle(Triangle *triangle, side_triangle side, double *side_value)
{
    check_getter_ptr(triangle, side_value)
    if (side == A_triangle) {
        *side_value = triangle->a;
    } else {
        if (side == B_triangle) {
            *side_value = triangle->b;
        } else {
            *side_value = triangle->c;
        }
    }
    return OK;
}

inline rc_triangle get_angle_triangle(Triangle *triangle, angle_triangle angle, double *angle_value)
{
    check_getter_ptr(triangle, angle_value)
    if (angle == alpha_triangle) {
        *angle_value = triangle->alpha;
    } else {
        if (angle == beta_triangle) {
            *angle_value = triangle->beta;
        } else {
            *angle_value = triangle->gamma;
        }
    }
    return OK;
}

inline rc_triangle get_square_triangle(Triangle *triangle, double *square)
{
    check_getter_ptr(triangle, square)
    *square = triangle->a * triangle->b * sin(triangle->gamma) / 2;
    return OK;
}

rc_triangle get_perimeter_triangle(Triangle *triangle, double *perimeter_value)
{
    check_getter_ptr(triangle, perimeter_value)
    *perimeter_value = triangle->a + triangle->b + triangle->c;
    return OK;
}

inline rc_triangle get_height_triangle(Triangle *triangle, side_triangle side, double *height_value)
{
    check_getter_ptr(triangle, height_value)
    double side_value;
    double angle_value;
    if (side == A_triangle) {
        side_value = triangle->b;
        angle_value = triangle->gamma;
    } else {
        if (side == B_triangle) {
            side_value = triangle->a;
            angle_value = triangle->gamma;
        } else {
            side_value = triangle->a;
            angle_value = triangle->beta;
        }
    }
    *height_value = side_value * sin(angle_value);
    return OK;
}

inline rc_triangle get_side_type_triangle(Triangle *triangle, side_types_triangle *side_type)
{
    check_getter_ptr(triangle, side_type)
    if (is_equal_d(triangle->a, triangle->b)) {
        if (is_equal_d(triangle->a, triangle->c) && is_equal_d(triangle->b, triangle->c)) {
            *side_type = equilateral;
        } else {
            *side_type = isosceles;
        }
    } else {
        if (is_equal_d(triangle->a, triangle->c) || is_equal_d(triangle->b, triangle->c)) {
            *side_type = isosceles;
        } else {
            *side_type = versatile;
        }
    }
    return OK;
}

inline rc_triangle get_angle_type_triangle(Triangle *triangle, angle_types_triangle *angle_type)
{
    check_getter_ptr(triangle, angle_type)
    double max_angle = max3_d(triangle->alpha, triangle->beta, triangle->gamma);
    if (is_greater_d(max_angle, M_PI_2)) {
        *angle_type = obtuse_angled;
    } else {
        if (is_equal_d(max_angle, M_PI_2)) {
            *angle_type = right_angled;
        } else {
            *angle_type = acute_angled;
        }
    }
    return OK;
}

/**
 * Setters
 */
rc_triangle set_3_sides_triangle(Triangle *triangle, double a, double b, double c)
{
    if (!triangle)
        return TRIANGLE_IS_NULL;
    check_init_values(a, b, c)
    set_sides_triangle_(triangle, a, b, c);
    calc_angles(triangle);
    return OK;
}

rc_triangle set_2_sides_1_angle_triangle(Triangle *triangle, double a, double b, double gamma)
{
    if (!triangle)
        return TRIANGLE_IS_NULL;
    check_init_values(a, b, gamma)
    if (!(is_below_d(gamma, M_PI)))
        return INCORRECT_ARGUMENT;
    set_sides_triangle_(triangle, a, b, sqrt((a * a) + (b * b) - (2 * a * b * cos(gamma))));
    calc_angles(triangle);
    return OK;
}

rc_triangle set_1_side_2_angles_triangle(Triangle *triangle, double a, double beta, double gamma)
{
    check_init_values(a, beta, gamma)
    if (!(is_below_d(beta + gamma, M_PI)))
        return INCORRECT_ARGUMENT;
    triangle->alpha = M_PI - (beta + gamma);
    triangle->beta  = beta;
    triangle->gamma = gamma;
    set_sides_triangle_(triangle, a, a * sin(beta)  / sin(triangle->alpha),
                        a * sin(gamma)  / sin(triangle->alpha));
    return OK;
}

rc_triangle set_side_triangle(Triangle *triangle, side_triangle side, double value)
{
    check_setter_arguments(triangle, value)
    double old_side_value;
    double *side_ptr;
    if (side == A_triangle) {
        old_side_value = triangle->a;
        side_ptr = &(triangle->a);
    } else {
        if (side == B_triangle) {
            old_side_value = triangle->b;
            side_ptr = &(triangle->b);
        } else {
            old_side_value = triangle->c;
            side_ptr = &(triangle->c);
        }
    }
    *side_ptr = value;
    if (!check_ineq(triangle)) {
        *side_ptr = old_side_value;
        return INCORRECT_ARGUMENT;
    }
    calc_angles(triangle);
    return OK;
}

// TODO
rc_triangle set_angle_triangle(Triangle *triangle, angle_triangle angle, double value)
{
    check_setter_arguments(triangle, value)

    return OK;
}

/**
 * Static functions
 */
static inline int is_greater_d(double first, double second)
{
    assert(isfinite(first));
    assert(isfinite(second));
    return (first - second) > EPSILON;
}

static inline int is_below_d(double first, double second)
{
    assert(isfinite(first));
    assert(isfinite(second));
    return (first - second) < -EPSILON;
}

static inline int check_ineq(Triangle *triangle)
{
    assert(triangle);
    assert(isfinite(triangle->a));
    assert(isfinite(triangle->b));
    assert(isfinite(triangle->c));
    return check_ineq_(triangle->a, triangle->b, triangle->c);
}

static inline int check_ineq_(double a, double b, double c)
{
    if (is_greater_d(b + c, a) && is_greater_d(a, fabs(b - c)))
        return TRUE;
    return FALSE;
}

static inline void calc_angles(Triangle *triangle)
{
    assert(triangle);
    assert(isfinite(triangle->a));
    assert(isfinite(triangle->b));
    assert(isfinite(triangle->c));
    triangle->alpha = acos(((triangle->b * triangle->b) + (triangle->c * triangle->c) - (triangle->a * triangle->a))
                            / (2 * triangle->b * triangle->c));
    triangle->beta = acos(((triangle->a * triangle->a) + (triangle->c * triangle->c) - (triangle->b * triangle->b))
                           / (2 * triangle->a * triangle->c));
    triangle->gamma = M_PI - (triangle->alpha + triangle->beta);
}

static inline int is_equal_d(double first, double second)
{
    return fabs(first - second) < EPSILON;
}

static inline double max3_d(double first, double second, double third)
{
    if (first > second) {
        if (first > third) {
            return first;
        } else {
            return third;
        }
    } else {
        if (second > third) {
            return second;
        } else {
            return third;
        }
    }
}

static inline double min3_d(double first, double second, double third)
{
    if (first < second) {
        if (first < third) {
            return first;
        } else {
            return third;
        }
    } else {
        if (second < third) {
            return second;
        } else {
            return third;
        }
    }
}

static inline void set_sides_triangle_(Triangle *triangle, double a, double b, double c)
{
    triangle->a = a;
    triangle->b = b;
    triangle->c = c;
}
