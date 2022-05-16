#ifndef FIRST_TRIANGLE_H
#define FIRST_TRIANGLE_H
#include "return_codes.h"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef struct Triangle Triangle;

typedef enum side_triangle {
    A_triangle = 0,
    B_triangle = 1,
    C_triangle = 2
} side_triangle;

typedef enum angle_triangle {
    alpha_triangle   = 0,
    beta_triangle    = 1,
    gamma_triangle   = 2
} angle_triangle;

typedef enum angle_types_triangle {
    acute_angled    = 0,
    right_angled    = 1,
    obtuse_angled   = 2
} angle_types_triangle;

typedef enum side_types_triangle {
    versatile       = 1,
    isosceles       = 2,
    equilateral     = 3
} side_types_triangle;

/**
 * Constructors
 */
rc_triangle init_3_sides_triangle(Triangle **triangle, double a, double b, double c);
rc_triangle init_2_sides_1_angle_triangle(Triangle **triangle, double a, double b, double gamma);
rc_triangle init_1_side_2_angles_triangle(Triangle **triangle, double a, double beta, double gamma);
/**
 * Destructor
 */
rc_triangle destroy_triangle(Triangle **triangle);

/**
 * Getters
 */
rc_triangle get_side_triangle(Triangle *triangle, side_triangle side, double *side_value);
rc_triangle get_angle_triangle(Triangle *triangle, angle_triangle angle, double *angle_value);
rc_triangle get_square_triangle(Triangle *triangle, double *square_value);
rc_triangle get_perimeter_triangle(Triangle *triangle, double *perimeter_value);
rc_triangle get_height_triangle(Triangle *triangle, side_triangle side, double *height_value);
rc_triangle get_side_type_triangle(Triangle *triangle, side_types_triangle *side_type);
rc_triangle get_angle_type_triangle(Triangle *triangle, angle_types_triangle *angle_type);

/**
 * Setters
 */
rc_triangle set_3_sides_triangle(Triangle *triangle, double a, double b, double c);
rc_triangle set_2_sides_1_angle_triangle(Triangle *triangle, double a, double b, double gamma);
rc_triangle set_1_side_2_angles_triangle(Triangle *triangle, double a, double beta, double gamma);
rc_triangle set_side_triangle(Triangle *triangle, side_triangle side, double value);
rc_triangle set_angle_triangle(Triangle *triangle, angle_triangle angle, double value);

/**
 * Static functions
 */
static inline int is_greater_d(double first, double second);
static inline int is_below_d(double first, double second);
static inline int check_ineq(Triangle *triangle);
static inline int check_ineq_(double a, double b, double c);
static inline void calc_angles(Triangle *triangle);
static inline int is_equal_d(double first, double second);
static inline double max3_d(double first, double second, double third);
static inline double min3_d(double first, double second, double third);
static inline void set_sides_triangle_(Triangle *triangle, double a, double b, double c);
#endif
