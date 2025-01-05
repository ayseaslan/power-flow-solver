#ifndef NETWORK_NETWORK_H_
#define NETWORK_NETWORK_H_

#include "types.h"

namespace pf_solver {

/**
 * @class Network
 * @brief Class to represent a power flow network instance.
 */
class Network {
 public:
  /**
   * @brief Constructs a Network object.
   * @param admittance_matrix The admittance matrix of the network.
   * @param buses The list of buses in the network.
   */
  Network(const AdmittanceMatrix& admittance_matrix, const BusVector& buses)
      : admittance_matrix_(admittance_matrix), buses_(buses) {
    num_buses_ = (int)buses_.size();
  }

  /**
   * @brief Destructor for the Network class.
   */
  ~Network() = default;

  /**
   * @brief Solve the power flow problem with genetic solver and fills bus
   * solutions.
   */
  void SolveGenetic(int population_size, double mutation_rate, int migrations,
                    double elite_selection_rate, int gaussseidel_iters,
                    int max_generations, double tolerance);

  /**
   * @brief Solve the power flow problem with Gauss-Seidel method and fills bus
   * solutions.
   */
  void SolveGaussSeidel(int max_iterations, double tolerance);

  /**
   * @brief Solve the power flow problem with Gauss-Seidel perturbation method
   * and fills bus solutions.
   */
  void SolvePerturbation(int max_iterations, double perturbation_rate,
                         double tolerance);

  /**
   * @brief Solve the power flow problem with Newton-Raphson method and fills
   * bus solutions.
   */
  void SolveNewtonRaphson(int max_iterations, double tolerance);

  /**
   * @brief Print the results of the power flow problem for each bus.
   */
  void PrintResults() const;

  /**
   * @brief Get the error in the power flow solution with Gauss-Seidel method.
   * @return The error in the power flow solution.
   */
  double GetPowerMismatchGaussSeidel() const {
    return power_mismatch_gauss_seidel_;
  }

  /**
   * @brief Get the error in the power flow solution with Genetic method.
   * @return The error in the power flow solution.
   */
  double GetPowerMismatchGenetic() const { return power_mismatch_genetic_; }

  /**
   * @brief Get the error in the power flow solution with Perturbation method.
   * @return The error in the power flow solution.
   */
  double GetPowerMismatchPerturbation() const {
    return power_mismatch_perturbation_;
  }

  /**
   * @brief Get the error in the power flow solution with Newton-Raphson method.
   * @return The error in the power flow solution.
   */
  double GetPowerMismatchNewtonRaphson() const {
    return power_mismatch_newtonraphson_;
  }

  /**
   * @brief Get the admittance matrix of the network.
   * @return The admittance matrix.
   */
  AdmittanceMatrix GetAdmittanceMatrix() const { return admittance_matrix_; };

  /**
   * @brief Get the list of buses in the network.
   * @return The list of buses.
   */
  BusVector GetBuses() const { return buses_; };

  /**
   * @brief Get the number of buses in the network.
   * @return The number of buses.
   */
  int GetNumBuses() const { return num_buses_; };

  /**
   * @brief Get the list of bus solutions.
   * @return The list of bus solutions.
   */
  BusSolutionVector GetBusSolutions() const { return bus_solutions_; };

 private:
  int num_buses_;  ///< The number of buses in the network.
  AdmittanceMatrix
      admittance_matrix_;            ///< The admittance matrix of the network.
  BusVector buses_;                  ///< The list of buses in the network.
  BusSolutionVector bus_solutions_;  ///< The list of bus solutions.
  double power_mismatch_gauss_seidel_;  ///< The error in the power flow
                                        ///< solution with GaussSeidel method.
  double power_mismatch_genetic_;  ///< The error in the power flow solution
                                   ///< with Genetic method.
  double power_mismatch_perturbation_;  ///< The error in the power flow
  ///< solution with Perturbation method.
  double power_mismatch_newtonraphson_;  ///< The error in the power flow
};
}  // namespace pf_solver

#endif  // NETWORK_NETWORK_H_
