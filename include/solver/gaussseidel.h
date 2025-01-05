#ifndef SOLVER_GAUSSSEIDEL_H_
#define SOLVER_GAUSSSEIDEL_H_

#include "network/network.h"

namespace gauss_seidel_pf_solver {
/**
 * @class GaussSeidelSolver
 * @brief Class to represent a Gauss-Seidel power flow solver.
 */
class GaussSeidelSolver {
 public:
  /**
   * @brief Constructs a GaussSeidelSolver object.
   * @param network The power flow network instance.
   * @param max_iterations The maximum number of iterations.
   * @param tolerance The convergence tolerance.
   */
  GaussSeidelSolver(const pf_solver::Network& network, int max_iterations,
                    double tolerance)
      : admittance_matrix_(network.GetAdmittanceMatrix()),
        buses_(network.GetBuses()),
        num_buses_(network.GetNumBuses()),
        max_iterations_(max_iterations),
        tolerance_(tolerance) {}

  /**
   * @brief Destructor for the GaussSeidelSolver class.
   */
  ~GaussSeidelSolver() = default;

  /**
   * @brief Solve the power flow problem using the Gauss-Seidel method.
   */
  void Solve();

  /**
   * @brief Get the list of bus solutions.
   * @return The list of bus solutions.
   */
  pf_solver::BusSolutionVector GetBusSolutions() const {
    return bus_solutions_;
  }

  /**
   * @brief Get the error in the power flow solution.
   * @return The error in the power flow solution.
   */
  double GetPowerMismatchError() const { return power_mismatch_; }

 private:
  int num_buses_;  ///< The number of buses in the network.
  pf_solver::AdmittanceMatrix
      admittance_matrix_;       ///< The admittance matrix of the network.
  pf_solver::BusVector buses_;  ///< The list of buses in the network.
  pf_solver::BusSolutionVector bus_solutions_;  ///< The list of bus solutions.
  int max_iterations_;     ///< The maximum number of iterations.
  double tolerance_;       ///< The convergence tolerance.
  double power_mismatch_;  ///< The error in the power flow solution.
};
}  // namespace gauss_seidel_pf_solver
#endif  // SOLVER_GAUSSSEIDEL_H_