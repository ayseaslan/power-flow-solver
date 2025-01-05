#ifndef MATPOWER_H_
#define MATPOWER_H_

#include "types.h"

namespace pf_solver {
namespace matpower {

/**
 * @brief Struct to represent a Matpower branch.
 */
struct MatpowerBranch {
  int from_bus_id;           ///< The from bus ID
  int to_bus_id;             ///< The to bus ID
  Complex admittance;        ///< The admittance of the branch
  Complex shunt_admittance;  ///< The shunt admittance of the branch
  /**
   * @brief Constructs a MatpowerBranch object.
   * @param from The from bus ID.
   * @param to The to bus ID.
   * @param r The resistance of the branch.
   * @param x The reactance of the branch.
   * @param g The conductance of the branch.
   * @param b The susceptance of the branch.
   * @param base_z The base impedance of the network.
   */
  MatpowerBranch(int from, int to, double r, double x, double g, double b,
                 double base_z)
      : from_bus_id(from),
        to_bus_id(to),
        admittance(1.0 / Complex(r / base_z, x / base_z)),
        shunt_admittance(Complex(g, b)) {}
};

/**
 * @brief Builds the admittance matrix from the Matpower branches.
 */
void BuildAdmittanceMatrix(const std::vector<MatpowerBranch>& branches,
                           AdmittanceMatrix& admittance_matrix_matpower) {
  // Initialize the admittance matrix
  for (const auto& branch : branches) {
    int from = branch.from_bus_id - 1;  // 1-indexed to 0-indexed
    int to = branch.to_bus_id - 1;
    // Add mutual admittance to the matrix
    admittance_matrix_matpower[from][to] -= branch.admittance;
    admittance_matrix_matpower[to][from] -= branch.admittance;
    // Add self admittance to the matrix
    admittance_matrix_matpower[from][from] +=
        branch.admittance + branch.shunt_admittance / 2.0;
    admittance_matrix_matpower[to][to] +=
        branch.admittance + branch.shunt_admittance / 2.0;
  }
}

}  // namespace matpower
}  // namespace pf_solver

#endif  // MATPOWER_H_