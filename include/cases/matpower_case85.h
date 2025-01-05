#ifndef CASES_MATPOWER_CASE85_H_
#define CASES_MATPOWER_CASE85_H_

#include "matpower.h"

namespace pf_solver {
namespace cases {
namespace matpower_case85 {
// See https://github.com/MATPOWER/matpower/blob/master/data/case85.m

// use per unit base values for per unit conversions
const double base_mva = 1.0;
const double base_kv = 11.0;
const double base_v = 1e3 * base_kv;   // kV to V
const double base_s = 1e6 * base_mva;  // MVA to VA
const double base_z = base_v * base_v / base_s;

BusVector buses = {
    Bus(0, BusType::kSlack, 1, 1, 0, 1.0, 1.0),
    Bus(1, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(2, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(3, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(4, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(5, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(6, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(7, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(8, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(9, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(10, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(11, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(12, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(13, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(14, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(15, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(16, BusType::kPQ, -112, -114.2629, 0, 1.1, 0.9),
    Bus(17, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(18, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(19, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(20, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(21, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(22, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(23, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(24, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(25, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(26, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(27, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(28, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(29, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(30, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(31, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(32, BusType::kPQ, -14, -14.2829, 0, 1.1, 0.9),
    Bus(33, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(34, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(35, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(36, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(37, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(38, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(39, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(40, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(41, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(42, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(43, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(44, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(45, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(46, BusType::kPQ, -14, -14.2829, 0, 1.1, 0.9),
    Bus(47, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(48, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(49, BusType::kPQ, -36.28, -37.013, 0, 1.1, 0.9),
    Bus(50, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(51, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(52, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(53, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(54, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(55, BusType::kPQ, -14, -14.2829, 0, 1.1, 0.9),
    Bus(56, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(57, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(58, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(59, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(60, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(61, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(62, BusType::kPQ, -14, -14.2829, 0, 1.1, 0.9),
    Bus(63, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(64, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(65, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(66, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(67, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(68, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(69, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(70, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(71, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(72, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(73, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(74, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(75, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(76, BusType::kPQ, -14, -14.2829, 0, 1.1, 0.9),
    Bus(77, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(78, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(79, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(80, BusType::kIsolated, 0, 0, 0, 1.1, 0.9),
    Bus(81, BusType::kPQ, -56, -57.1314, 0, 1.1, 0.9),
    Bus(82, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
    Bus(83, BusType::kPQ, -14, -14.2829, 0, 1.1, 0.9),
    Bus(84, BusType::kPQ, -35.28, -35.9928, 0, 1.1, 0.9),
};

/**
 * @brief Get the buses of the 85 bus network.
 */
BusVector GetBuses() {
  // conversion from kW to MW
  for (auto& bus : buses) {
    if (bus.bus_type == BusType::kPQ) {
      bus.bus_given_values.first = bus.bus_given_values.first / 1e3;
      bus.bus_given_values.second = bus.bus_given_values.second / 1e3;
    }
  }
  return buses;
}

// MATPOWER case 85 branch data
const std::vector<pf_solver::matpower::MatpowerBranch> branches = {
    pf_solver::matpower::MatpowerBranch(1, 2, 0.108, 0.075, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(2, 3, 0.163, 0.112, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(3, 4, 0.217, 0.149, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(4, 5, 0.108, 0.074, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(5, 6, 0.435, 0.298, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(6, 7, 0.272, 0.186, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(7, 8, 1.197, 0.82, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(8, 9, 0.108, 0.074, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(9, 10, 0.598, 0.41, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(10, 11, 0.544, 0.373, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(11, 12, 0.544, 0.373, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(12, 13, 0.598, 0.41, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(13, 14, 0.272, 0.186, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(14, 15, 0.326, 0.223, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(2, 16, 0.728, 0.302, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(3, 17, 0.455, 0.189, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(5, 18, 0.82, 0.34, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(18, 19, 0.637, 0.264, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(19, 20, 0.455, 0.189, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(20, 21, 0.819, 0.34, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(21, 22, 1.548, 0.642, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(19, 23, 0.182, 0.075, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(7, 24, 0.91, 0.378, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(8, 25, 0.455, 0.189, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(25, 26, 0.364, 0.151, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(26, 27, 0.546, 0.226, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(27, 28, 0.273, 0.113, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(28, 29, 0.546, 0.226, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(29, 30, 0.546, 0.226, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(30, 31, 0.273, 0.113, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(31, 32, 0.182, 0.075, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(32, 33, 0.182, 0.075, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(33, 34, 0.819, 0.34, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(34, 35, 0.637, 0.264, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(35, 36, 0.182, 0.075, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(26, 37, 0.364, 0.151, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(27, 38, 1.002, 0.416, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(29, 39, 0.546, 0.226, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(32, 40, 0.455, 0.189, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(40, 41, 1.002, 0.416, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(41, 42, 0.273, 0.113, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(41, 43, 0.455, 0.189, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(34, 44, 1.002, 0.416, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(44, 45, 0.911, 0.378, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(45, 46, 0.911, 0.378, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(46, 47, 0.546, 0.226, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(35, 48, 0.637, 0.264, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(48, 49, 0.182, 0.075, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(49, 50, 0.364, 0.151, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(50, 51, 0.455, 0.189, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(48, 52, 1.366, 0.567, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(52, 53, 0.455, 0.189, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(53, 54, 0.546, 0.226, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(52, 55, 0.546, 0.226, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(49, 56, 0.546, 0.226, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(9, 57, 0.273, 0.113, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(57, 58, 0.819, 0.34, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(58, 59, 0.182, 0.075, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(58, 60, 0.546, 0.226, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(60, 61, 0.728, 0.302, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(61, 62, 1.002, 0.415, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(60, 63, 0.182, 0.075, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(63, 64, 0.728, 0.302, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(64, 65, 0.182, 0.075, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(65, 66, 0.182, 0.075, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(64, 67, 0.455, 0.189, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(67, 68, 0.91, 0.378, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(68, 69, 1.092, 0.453, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(69, 70, 0.455, 0.189, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(70, 71, 0.546, 0.226, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(67, 72, 0.182, 0.075, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(68, 73, 1.184, 0.491, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(73, 74, 0.273, 0.113, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(73, 75, 1.002, 0.416, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(70, 76, 0.546, 0.226, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(65, 77, 0.091, 0.037, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(10, 78, 0.637, 0.264, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(67, 79, 0.546, 0.226, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(12, 80, 0.728, 0.302, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(80, 81, 0.364, 0.151, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(81, 82, 0.091, 0.037, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(81, 83, 1.092, 0.453, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(83, 84, 1.002, 0.416, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(13, 85, 0.819, 0.34, 0, 0, base_z)};

/**
 * @brief Get the admittance matrix of the 85 bus network.
 */
AdmittanceMatrix GetAdmittanceMatrix() {
  Complex2D admittance_matrix_matpower(85, Complex1D(85, {0.0, 0.0}));
  pf_solver::matpower::BuildAdmittanceMatrix(branches,
                                             admittance_matrix_matpower);
  return admittance_matrix_matpower;
}

}  // namespace matpower_case85
}  // namespace cases
}  // namespace pf_solver

#endif  // CASES_MATPOWER_CASE85_H_