project(2020_LS_zadanie_A3 C)

set(CMAKE_C_STANDARD 99)

set(files
        main.c
        constants.c

        arguments/arguments.c
        arguments/tables/argumentsTable.c
        arguments/dumpArguments.c
        arguments/tables/stringOptionTables.c
        arguments/tables/intOptionTables.c
        arguments/tables/parameterTables.c
        arguments/printUsage.c

        core/error.c
        core/exit.c
        core/file.c
        core/matrix.c
        core/matrixOperations.c
        core/output.c
        core/parse.c
        core/rootPath.c
        core/vector.c

        data/temperature.c

        equations/simulation/acceleration.c
        equations/simulation/dynamics.c
        equations/general.c
        equations/polynomial.c
        equations/simulation/velocity.c

        solvers/simulation/euler.c
        solvers/integrateRiemannSum.c
        solvers/linear/linearEquationSystem.c
        solvers/linear/linearLeastSquares.c
        solvers/linear/linearLupDecompose.c
        solvers/linear/linearLupNormalize.c
        solvers/linear/linearLupSolve.c
        solvers/simulation/rungeKutta.c
        solvers/simulation/solveGeneric.c
        solvers/simulation/statistics.c
        )

add_executable(2020_LS_zadanie_A3 ${files})
target_link_libraries(2020_LS_zadanie_A3 PRIVATE m)

# Uncomment this to use statically generated root path
# target_compile_definitions(2020_LS_zadanie_A3 PRIVATE USE_STATIC_ROOT_PATH)
target_compile_definitions(2020_LS_zadanie_A3 PRIVATE ROOT_PATH="${CMAKE_CURRENT_BINARY_DIR}")

# Copy temperature.txt to output directory
add_custom_command(TARGET 2020_LS_zadanie_A3 POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/data/temperature.txt"
        "${CMAKE_CURRENT_BINARY_DIR}/data/temperature.txt"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/data/temperature.txt"
        COMMENT "Copying \"data/temperature.txt\""
        )
