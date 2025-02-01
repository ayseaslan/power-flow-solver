add_executable(solver main.cc)

target_link_libraries(solver PRIVATE network_lib genetic_solver_lib gaussseidel_solver_lib newton_solver_lib)

