project(2020_LS_zadanie_A C)

set(files
        main.c
        acceleration.c
        utility.c

        analytical.c

        solvers/euler.c
        solvers/rungeKutta.c
        )

add_executable(2020_LS_zadanie_A ${files})
target_link_libraries(2020_LS_zadanie_A PRIVATE m)
