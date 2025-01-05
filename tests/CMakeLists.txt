add_executable(
  solver_test
  maths_test.cc
)

target_link_libraries(
  solver_test
  GTest::gtest_main
  network_lib
)

include(GoogleTest)
gtest_discover_tests(solver_test)