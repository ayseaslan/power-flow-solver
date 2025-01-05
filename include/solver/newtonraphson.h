#ifndef SOLVER_NEWTONRAPHSON_H_
#define SOLVER_NEWTONRAPHSON_H_

#include "network/network.h"
namespace newtonraphson_pf_solver {
/**
 * @class NewtonRaphsonSolver
 * @brief Class to represent a Newton-Raphson power flow solver.
 */
class NewtonRaphsonSolver {
 public:
  /**
   * @brief Constructs a NewtonRaphsonSolver object.
   * @param network The power flow network instance.
   * @param max_iterations The maximum number of iterations.
   * @param tolerance The convergence tolerance.
   */
  NewtonRaphsonSolver(const pf_solver::Network& network, int max_iterations,
                      double tolerance)
      : admittance_matrix_(network.GetAdmittanceMatrix()),
        buses_(network.GetBuses()),
        num_buses_(network.GetNumBuses()),
        max_iterations_(max_iterations),
        tolerance_(tolerance) {
    AssignNonPQBusIds();
  }

  /**
   * @brief Destructor for the NewtonRaphsonSolver class.
   */
  ~NewtonRaphsonSolver() = default;

  /**
   * @brief Solve the power flow problem using the Newton-Raphson method.
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
  pf_solver::IndexVector slack_buses_;     ///< The list of slack buses.
  pf_solver::IndexVector pv_buses_;        ///< The list of PV buses.
  pf_solver::IndexVector isolated_buses_;  ///< The list of isolated buses.

  /**
   * @brief Jacobian step for the Newton-Raphson method.
   */
  int SolveWithJacobian();

  /**
   * @brief Assigns bus ids for non-PQ buses.
   */
  void AssignNonPQBusIds();

  /**
   * @brief Checks if the angle is valid.
   * @param angle The angle to check.
   * @return True if the angle is valid, false otherwise.
   */
  bool ValidAngle(double angle) const;

  /**
   * @brief Checks if the magnitude is valid.
   * @param magnitude The magnitude to check.
   * @param bus_id The bus id.
   * @return True if the magnitude is valid, false otherwise.
   */
  bool ValidMagnitude(double magnitude, int bus_id) const;
};

}  // namespace newtonraphson_pf_solver
#endif  // SOLVER_NEWTONRAPHSON_H_