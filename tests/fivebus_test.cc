#include <gtest/gtest.h>

#include "cases/fivebus_maple.h"
#include "network/network.h"

using namespace pf_solver;

/**
 * @brief Test the five bus network case.
 * Solutions are compared with the Maple example.
 * see https://www.maplesoft.com/Applications/Detail.aspx?id=154675
 * for the reference solutions.
 */
TEST(FiveBusCase, LoadFlowCases) {
  Network network(cases::fivebus_maple::GetAdmittanceMatrix(),
                  cases::fivebus_maple::GetBuses());
  network.SolveNewtonRaphson(
      5, 1e-3);  // 5 iterations should be enough for newton raphson
  const auto bus_solutions = network.GetBusSolutions();
  for (const auto& bus_solution : bus_solutions) {
    if (bus_solution.bus_id == 0) {
      EXPECT_NEAR(bus_solution.voltage_magnitude, 1.04, 1e-2);
      EXPECT_NEAR(bus_solution.voltage_angle, 0.0, 1e-2);
    }
    if (bus_solution.bus_id == 1) {
      EXPECT_NEAR(bus_solution.voltage_magnitude, 0.96, 1e-2);
      EXPECT_NEAR(bus_solution.voltage_angle, -0.11, 1e-2);
    }
    if (bus_solution.bus_id == 2) {
      EXPECT_NEAR(bus_solution.voltage_magnitude, 1.02, 1e-2);
      EXPECT_NEAR(bus_solution.voltage_angle, -0.06, 1e-2);
    }
    if (bus_solution.bus_id == 3) {
      EXPECT_NEAR(bus_solution.voltage_magnitude, 0.926, 1e-2);
      EXPECT_NEAR(bus_solution.voltage_angle, -0.19, 1e-2);
    }
    if (bus_solution.bus_id == 4) {
      EXPECT_NEAR(bus_solution.voltage_magnitude, 0.97, 1e-2);
      EXPECT_NEAR(bus_solution.voltage_angle, -0.11, 1e-2);
    }
  }
}
