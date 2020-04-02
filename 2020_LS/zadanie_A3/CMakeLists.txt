project(2020_LS_zadanie_A3 C)

set(files
        main.c
        constants.c

        arguments/arguments.c
        arguments/argumentsTable.c
        arguments/dataFileTables.c
        arguments/parameterTables.c

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

        equations/acceleration.c
        equations/analytical.c
        equations/general.c
        equations/polynomial.c
        equations/velocity.c

        solvers/euler.c
        solvers/linearLeastSquares.c
        solvers/rungeKutta.c
        solvers/solveGeneric.c
        solvers/statistics.c
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
