#ifndef CASES_FIVEBUS_MAPLE_H_
#define CASES_FIVEBUS_MAPLE_H_

#include "types.h"

namespace pf_solver {
namespace cases {
namespace fivebus_maple {
// see https://www.maplesoft.com/Applications/Detail.aspx?id=154675 for the
// details of the example network

Bus slack = Bus(0, BusType::kSlack, 1.04, 0.0, 0, 1.04, 1.04);
Bus pq_1 = Bus(1, BusType::kPQ, -1.15, -0.6, 0, 1.06, 0.7);
Bus pv_1 = Bus(2, BusType::kPV, 1.1, 1.02, 0, 1.06, 0.7);
Bus pq_2 = Bus(3, BusType::kPQ, -0.7, -0.3, 0, 1.06, 0.7);
Bus pq_3 = Bus(4, BusType::kPQ, -0.85, -0.4, 0, 1.06, 0.7);
BusVector buses = {slack, pq_1, pv_1, pq_2, pq_3};

/**
 * @brief Get the buses of the five bus network.
 */
BusVector GetBuses() { return buses; }

/**
 * @brief Get the admittance matrix of the five bus network.
 */
AdmittanceMatrix GetAdmittanceMatrix() {
  AdmittanceMatrix admittance_matrix = {
      {Complex(3.24, -13.06), Complex(-1.40, 5.60), Complex(0.0, 0.0),
       Complex(0.0, 0.0), Complex(-1.84, 7.48)},
      {Complex(-1.40, 5.60), Complex(3.24, -13.05), Complex(-1.84, 7.48),
       Complex(0.0, 0.0), Complex(0.0, 0.0)},
      {Complex(0.0, 0.0), Complex(-1.84, 7.48), Complex(3.67, -14.68),
       Complex(-0.70, 2.80), Complex(-1.13, 4.48)},
      {
          Complex(0.0, 0.0),
          Complex(0.0, 0.0),
          Complex(-0.70, 2.80),
          Complex(1.63, -6.44),
          Complex(-0.93, 3.73),
      },
      {Complex(-1.84, 7.48), Complex(0.0, 0.0), Complex(-1.13, 4.48),
       Complex(-0.93, 3.73), Complex(3.90, -15.61)},
  };
  return admittance_matrix;
}

}  // namespace fivebus_maple
}  // namespace cases
}  // namespace pf_solver
#endif  // CASES_FIVEBUS_MAPLE_H_