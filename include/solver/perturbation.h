#ifndef SOLVER_PERTURBATION_H_
#define SOLVER_PERTURBATION_H_

#include "network/network.h"

namespace perturbation_pf_solver {
/**
 * @class PerturbationSolver
 * @brief Class to represent a perturb and search power flow solver.
 */
class PerturbationSolver {
 public:
  /**
   * @brief Constructs a PerturbationSolver object.
   * @param network The power flow network instance.
   * @param max_iterations The maximum number of iterations.
   * @param perturbation_rate The perturbation rate.
   * @param tolerance The convergence tolerance.
   */
  PerturbationSolver(const pf_solver::Network& network, int max_iterations,
                     double perturbation_rate, double tolerance)
      : admittance_matrix_(network.GetAdmittanceMatrix()),
        buses_(network.GetBuses()),
        num_buses_(network.GetNumBuses()),
        max_iterations_(max_iterations),
        perturbation_rate_(perturbation_rate),
        tolerance_(tolerance) {}

  /**
   * @brief Destructor for the PerturbationSolver class.
   */
  ~PerturbationSolver() = default;

  /**
   * @brief Solve the power flow problem using the perturb and search method.
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
  int max_iterations_;        ///< The maximum number of iterations.
  double perturbation_rate_;  ///< The perturbation rate.
  double tolerance_;          ///< The convergence tolerance.
  double power_mismatch_;     ///< The error in the power flow solution.
};
}  // namespace perturbation_pf_solver

#endif  // SOLVER_PERTURBATION_H_