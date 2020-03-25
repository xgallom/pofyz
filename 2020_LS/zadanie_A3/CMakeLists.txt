project(2020_LS_zadanie_A3 C)

set(files
        main.c
        arguments.c
        constants.c
        parameterTables.c

        core/error.c
        core/exit.c
        core/file.c
        core/output.c
        core/parse.c
        core/vector.c

        equations/acceleration.c
        equations/analytical.c
        equations/general.c
        equations/velocity.c

        solvers/euler.c
        solvers/rungeKutta.c
        solvers/solveGeneric.c
        solvers/statistics.c
        )

add_executable(2020_LS_zadanie_A3 ${files})
target_link_libraries(2020_LS_zadanie_A3 PRIVATE m)
