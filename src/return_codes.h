#ifndef FIRSTLAB_RETURN_CODES_H
#define FIRSTLAB_RETURN_CODES_H

typedef enum rc_triangle {
    OK                      = 0,
    INCORRECT_ARGUMENT      = 1,
    TRIANGLE_IS_NULL        = 2,
    IS_NOT_FINITE_ARGUMENT  = 3,
    ARGUMENT_IS_NULL        = 4,
    MEMORY_ALLOCATION_ERROR = 5
} rc_triangle;

#endif
