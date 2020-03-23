project(2020_LS_cvicenie_05_2 C)

set(files
        main.c
        arguments.c
        constants.c

        core/error.c
        core/exit.c
        core/file.c
        core/output.c
        core/parse.c
        core/vector.c

        equations/acceleration.c
        equations/analytical.c
        equations/velocity.c

        solvers/euler.c
        solvers/solveGeneric.c
        solvers/rungeKutta.c
        solvers/statistics.c
        )

add_executable(2020_LS_cvicenie_05_2 ${files})
target_link_libraries(2020_LS_cvicenie_05_2 PRIVATE m)
