#ifndef CASES_MATPOWER_CASE22_H_
#define CASES_MATPOWER_CASE22_H_

#include "matpower.h"

namespace pf_solver {
namespace cases {
namespace matpower_case22 {
// See https://github.com/MATPOWER/matpower/blob/master/data/case22.m

// use per unit base values for per unit conversions
const double base_mva = 1.0;
const double base_kv = 11.0;
const double base_v = 1e3 * base_kv;   // kV to V
const double base_s = 1e6 * base_mva;  // MVA to VA
const double base_z = base_v * base_v / base_s;

Bus slack = Bus(0, BusType::kSlack, 1.0, 0.0, 0, 1.0, 1.0);
Bus pq_1 = Bus(1, BusType::kPQ, -16.78, -20.91, 0, 1.1, 0.9);
Bus pq_2 = Bus(2, BusType::kPQ, -16.78, -20.91, 0, 1.1, 0.9);
Bus pq_3 = Bus(3, BusType::kPQ, -33.8, -37.32, 0, 1.1, 0.9);
Bus pq_4 = Bus(4, BusType::kPQ, -14.56, -12.52, 0, 1.1, 0.9);
Bus pq_5 = Bus(5, BusType::kPQ, -10.49, -14.21, 0, 1.1, 0.9);
Bus pq_6 = Bus(6, BusType::kPQ, -8.821, -11.66, 0, 1.1, 0.9);
Bus pq_7 = Bus(7, BusType::kPQ, -14.35, -18.59, 0, 1.1, 0.9);
Bus pq_8 = Bus(8, BusType::kPQ, -19.31, -25.87, 0, 1.1, 0.9);
Bus pq_9 = Bus(9, BusType::kPQ, -14.35, -18.59, 0, 1.1, 0.9);
Bus pq_10 = Bus(10, BusType::kPQ, -16.27, -19.48, 0, 1.1, 0.9);
Bus pq_11 = Bus(11, BusType::kPQ, -16.27, -19.48, 0, 1.1, 0.9);
Bus pq_12 = Bus(12, BusType::kPQ, -82.13, -71.65, 0, 1.1, 0.9);
Bus pq_13 = Bus(13, BusType::kPQ, -34.71, -30.12, 0, 1.1, 0.9);
Bus pq_14 = Bus(14, BusType::kPQ, -34.71, -30.12, 0, 1.1, 0.9);
Bus pq_15 = Bus(15, BusType::kPQ, -80.31, -70.12, 0, 1.1, 0.9);
Bus pq_16 = Bus(16, BusType::kPQ, -49.62, -47.82, 0, 1.1, 0.9);
Bus pq_17 = Bus(17, BusType::kPQ, -49.62, -47.82, 0, 1.1, 0.9);
Bus pq_18 = Bus(18, BusType::kPQ, -43.77, -38.93, 0, 1.1, 0.9);
Bus pq_19 = Bus(19, BusType::kPQ, -37.32, -35.96, 0, 1.1, 0.9);
Bus pq_20 = Bus(20, BusType::kPQ, -37.32, -35.96, 0, 1.1, 0.9);
Bus pq_21 = Bus(21, BusType::kPQ, -31.02, -29.36, 0, 1.1, 0.9);

BusVector buses = {slack, pq_1,  pq_2,  pq_3,  pq_4,  pq_5,  pq_6,  pq_7,
                   pq_8,  pq_9,  pq_10, pq_11, pq_12, pq_13, pq_14, pq_15,
                   pq_16, pq_17, pq_18, pq_19, pq_20, pq_21};

/**
 * @brief Get the buses of the MATPOWER case 22 network.
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

// MATPOWER case 22 branch data
const std::vector<pf_solver::matpower::MatpowerBranch> branches = {
    pf_solver::matpower::MatpowerBranch(1, 2, 0.3664, 0.1807, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(2, 3, 0.0547, 0.0282, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(2, 4, 0.5416, 0.2789, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(4, 5, 0.193, 0.099, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(4, 9, 0.7431, 0.3827, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(5, 6, 1.311, 0.6752, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(6, 7, 0.0598, 0.0308, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(6, 8, 0.2905, 0.1496, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(9, 10, 0.0547, 0.0282, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(9, 11, 0.675, 0.3481, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(11, 12, 0.0547, 0.0282, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(11, 13, 0.3942, 0.203, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(13, 14, 1.046, 0.5388, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(14, 15, 0.022, 0.0116, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(14, 16, 0.0547, 0.0282, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(16, 17, 0.3212, 0.1654, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(17, 18, 0.0949, 0.0488, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(17, 19, 0.574, 0.2959, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(19, 20, 0.1292, 0.066, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(20, 21, 0.0871, 0.045, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(20, 22, 0.5329, 0.2744, 0, 0, base_z),
};

/**
 * @brief Get the admittance matrix of the MATPOWER case 22 network.
 */
AdmittanceMatrix GetAdmittanceMatrix() {
  Complex2D admittance_matrix_matpower(22, Complex1D(22, {0.0, 0.0}));
  pf_solver::matpower::BuildAdmittanceMatrix(branches,
                                             admittance_matrix_matpower);
  return admittance_matrix_matpower;
}

}  // namespace matpower_case22
}  // namespace cases
}  // namespace pf_solver

#endif  // CASES_MATPOWER_CASE22_H_