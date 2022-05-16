add_library(
        triangle
        triangle.c
)

add_executable(
        FirstLab
        main.c
)

target_link_libraries(triangle m)
target_link_libraries(FirstLab triangle)