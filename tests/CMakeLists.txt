
# discover all .cc files in the current directory
file(GLOB TEST_SOURCES "*.cc")


add_executable(
  solver_test
  ${TEST_SOURCES}
)

target_link_libraries(
  solver_test
  GTest::gtest_main
  network_lib 
  genetic_solver_lib 
  gaussseidel_solver_lib 
  newton_solver_lib
)

include(GoogleTest)
gtest_discover_tests(solver_test)