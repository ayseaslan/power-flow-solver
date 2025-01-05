#ifndef CASES_IEEE33_H_
#define CASES_IEEE33_H_

#include "matpower.h"

namespace pf_solver {
namespace cases {
namespace ieee33 {
// See
// https://github.com/TesslaRay/Power-flow-solution-in-distribution-networks/blob/master/Backward_algorithm.m
// and https://www.jmest.org/wp-content/uploads/JMESTN42354194.pdf

// use per unit base values for per unit conversions
const double base_mva = 100.0;
const double base_kv = 11.0;
const double base_v = 1e3 * base_kv;   // kV to V
const double base_s = 1e6 * base_mva;  // MVA to VA
const double base_z = base_v * base_v / base_s;

Bus slack = Bus(0, BusType::kSlack, 1.0, 0.0, 0, 1.0, 1.0);
Bus pq_1 = Bus(1, BusType::kPQ, -100.0, -60.0, 0, 1.1, 0.6);
Bus pq_2 = Bus(2, BusType::kPQ, -90.0, -40.0, 0, 1.1, 0.6);
Bus pq_3 = Bus(3, BusType::kPQ, -120.0, -80.0, 0, 1.1, 0.6);
Bus pq_4 = Bus(4, BusType::kPQ, -60.0, -30.0, 0, 1.1, 0.6);
Bus pq_5 = Bus(5, BusType::kPQ, -60.0, -20.0, 0, 1.1, 0.6);
Bus pq_6 = Bus(6, BusType::kPQ, -200.0, -100.0, 0, 1.1, 0.6);
Bus pq_7 = Bus(7, BusType::kPQ, -200.0, -100.0, 0, 1.1, 0.6);
Bus pq_8 = Bus(8, BusType::kPQ, -60.0, -20.0, 0, 1.1, 0.6);
Bus pq_9 = Bus(9, BusType::kPQ, -60.0, -20.0, 0, 1.1, 0.6);
Bus pq_10 = Bus(10, BusType::kPQ, -45.0, -30.0, 0, 1.1, 0.6);
Bus pq_11 = Bus(11, BusType::kPQ, -60.0, -35.0, 0, 1.1, 0.6);
Bus pq_12 = Bus(12, BusType::kPQ, -60.0, -35.0, 0, 1.1, 0.6);
Bus pq_13 = Bus(13, BusType::kPQ, -120.0, -80.0, 0, 1.1, 0.6);
Bus pq_14 = Bus(14, BusType::kPQ, -60.0, -10.0, 0, 1.1, 0.6);
Bus pq_15 = Bus(15, BusType::kPQ, -60.0, -20.0, 0, 1.1, 0.6);
Bus pq_16 = Bus(16, BusType::kPQ, -60.0, -20.0, 0, 1.1, 0.6);
Bus pq_17 = Bus(17, BusType::kPQ, -90.0, -40.0, 0, 1.1, 0.6);
Bus pq_18 = Bus(18, BusType::kPQ, -90.0, -40.0, 0, 1.1, 0.6);
Bus pq_19 = Bus(19, BusType::kPQ, -90.0, -40.0, 0, 1.1, 0.6);
Bus pq_20 = Bus(20, BusType::kPQ, -90.0, -40.0, 0, 1.1, 0.6);
Bus pq_21 = Bus(21, BusType::kPQ, -90.0, -40.0, 0, 1.1, 0.6);
Bus pq_22 = Bus(22, BusType::kPQ, -90.0, -50.0, 0, 1.1, 0.6);
Bus pq_23 = Bus(23, BusType::kPQ, -420.0, -200.0, 0, 1.1, 0.6);
Bus pq_24 = Bus(24, BusType::kPQ, -420.0, -200.0, 0, 1.1, 0.6);
Bus pq_25 = Bus(25, BusType::kPQ, -60.0, -25.0, 0, 1.1, 0.6);
Bus pq_26 = Bus(26, BusType::kPQ, -60.0, -25.0, 0, 1.1, 0.6);
Bus pq_27 = Bus(27, BusType::kPQ, -60.0, -20.0, 0, 1.1, 0.6);
Bus pq_28 = Bus(28, BusType::kPQ, -120.0, -70.0, 0, 1.1, 0.6);
Bus pq_29 = Bus(29, BusType::kPQ, -200.0, -600.0, 0, 1.1, 0.6);
Bus pq_30 = Bus(30, BusType::kPQ, -150.0, -70.0, 0, 1.1, 0.6);
Bus pq_31 = Bus(31, BusType::kPQ, -210.0, -100.0, 0, 1.1, 0.6);
Bus pq_32 = Bus(32, BusType::kPQ, -60.0, -40.0, 0, 1.1, 0.6);

BusVector buses = {slack, pq_1,  pq_2,  pq_3,  pq_4,  pq_5,  pq_6,
                   pq_7,  pq_8,  pq_9,  pq_10, pq_11, pq_12, pq_13,
                   pq_14, pq_15, pq_16, pq_17, pq_18, pq_19, pq_20,
                   pq_21, pq_22, pq_23, pq_24, pq_25, pq_26, pq_27,
                   pq_28, pq_29, pq_30, pq_31, pq_32};
/**
 * @brief Get the buses of the IEEE 33 bus network.
 */
BusVector GetBuses() {
  // conversion from kW to MW
  for (auto& bus : buses) {
    if (bus.bus_type == BusType::kPQ) {
      bus.bus_given_values.first =
          bus.bus_given_values.first / (1e3 * base_mva);
      bus.bus_given_values.second =
          bus.bus_given_values.second / (1e3 * base_mva);
    }
  }
  return buses;
}

const std::vector<pf_solver::matpower::MatpowerBranch> branches = {
    pf_solver::matpower::MatpowerBranch(1, 2, 0.0922, 0.0470, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(2, 3, 0.4930, 0.2511, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(3, 4, 0.3660, 0.1864, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(4, 5, 0.3811, 0.1941, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(5, 6, 0.8190, 0.7070, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(6, 7, 0.1872, 0.6188, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(7, 8, 0.7114, 0.2351, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(8, 9, 1.0300, 0.7400, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(9, 10, 1.0440, 0.7400, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(10, 11, 0.1966, 0.0650, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(11, 12, 0.3744, 0.1238, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(12, 13, 1.4680, 1.1550, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(13, 14, 0.5416, 0.7129, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(14, 15, 0.5910, 0.5260, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(15, 16, 0.7463, 0.5450, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(16, 17, 1.2890, 1.7210, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(17, 18, 0.7320, 0.5740, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(2, 19, 0.1640, 0.1565, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(19, 20, 1.5042, 1.3554, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(20, 21, 0.4095, 0.4784, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(21, 22, 0.7089, 0.9373, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(3, 23, 0.4512, 0.3083, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(23, 24, 0.8980, 0.7091, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(24, 25, 0.8960, 0.7011, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(6, 26, 0.2030, 0.1034, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(26, 27, 0.2842, 0.1447, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(27, 28, 1.0590, 0.9337, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(28, 29, 0.8042, 0.7006, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(29, 30, 0.5075, 0.2585, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(30, 31, 0.9744, 0.9630, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(31, 32, 0.3105, 0.3619, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(32, 33, 0.3410, 0.5302, 0, 0, base_z),

};

/**
 * @brief Get the admittance matrix of the IEEE 33 bus network.
 */
AdmittanceMatrix GetAdmittanceMatrix() {
  Complex2D admittance_matrix_matpower(33, Complex1D(33, {0.0, 0.0}));
  pf_solver::matpower::BuildAdmittanceMatrix(branches,
                                             admittance_matrix_matpower);
  return admittance_matrix_matpower;
}

}  // namespace ieee33
}  // namespace cases
}  // namespace pf_solver

#endif  // CASES_IEEE33_H_