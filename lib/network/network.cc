#include "network/network.h"

#include <fstream>
#include <iostream>

#include "solver/gaussseidel.h"
#include "solver/genetic.h"
#include "solver/newtonraphson.h"
#include "solver/perturbation.h"

namespace pf_solver {

/**
 * @brief Prints the results of the power flow problem for each bus.
 */
void Network::PrintResults() const {
  std::ofstream log_file("pf_results.txt");
  if (!log_file.is_open()) {
    std::cerr << "Failed to open log file." << std::endl;
    return;
  }
  for (const auto& bus_solution : bus_solutions_) {
    log_file << "Bus ID: " << bus_solution.bus_id << std::endl;
    std::cout << "Bus ID: " << bus_solution.bus_id << std::endl;
    log_file << "Voltage Magnitude: " << bus_solution.voltage_magnitude
             << " p.u." << std::endl;
    std::cout << "Voltage Magnitude: " << bus_solution.voltage_magnitude
              << " p.u." << std::endl;
    log_file << "Voltage Angle: " << bus_solution.voltage_angle << " radians"
             << std::endl;
    std::cout << "Voltage Angle: " << bus_solution.voltage_angle << " radians"
              << std::endl;
    log_file << "Active Power: " << bus_solution.active_power << " MW"
             << std::endl;
    std::cout << "Active Power: " << bus_solution.active_power << " MW"
              << std::endl;
    log_file << "Reactive Power: " << bus_solution.reactive_power << " MVar"
             << std::endl;
    std::cout << "Reactive Power: " << bus_solution.reactive_power << " MVar"
              << std::endl;
  }
  log_file.close();
}

/**
 * @brief Solve the power flow problem and fills bus solutions.
 */
void Network::SolveGenetic(int population_size, double mutation_rate,
                           int migrations, double elite_selection_rate,
                           int gaussseidel_iters, int max_generations,
                           double tolerance) {
  // Solve the power flow problem using the genetic algorithm
  genetic_pf_solver::GeneticSolver solver(
      *this, population_size, mutation_rate, migrations, elite_selection_rate,
      gaussseidel_iters, max_generations, tolerance);
  solver.Solve();
  const auto power = solver.GetBusPowerSolution();
  const auto voltage = solver.GetBusVoltageSolution();
  for (int i = 0; i < power.size(); ++i) {
    bus_solutions_.push_back(BusSolution(
        power[i].bus_id, voltage[i].voltage_magnitude, voltage[i].voltage_angle,
        power[i].active_power, power[i].reactive_power));
  }
  power_mismatch_genetic_ = solver.GetPowerMismatchError();
}

/**
 * @brief Solve the power flow problem with Gauss-Seidel method and fills bus
 * solutions.
 */
void Network::SolveGaussSeidel(int max_iterations, double tolerance) {
  // Solve the power flow problem using the Gauss-Seidel method
  gauss_seidel_pf_solver::GaussSeidelSolver solver(*this, max_iterations,
                                                   tolerance);
  solver.Solve();
  const auto bus_solutions = solver.GetBusSolutions();
  for (const auto& bus_solution : bus_solutions) {
    bus_solutions_.push_back(bus_solution);
  }
  power_mismatch_gauss_seidel_ = solver.GetPowerMismatchError();
}

/**
 * @brief Solve the power flow problem with Gauss-Seidel perturbation method
 * and fills bus solutions.
 */
void Network::SolvePerturbation(int max_iterations, double perturbation_rate,
                                double tolerance) {
  perturbation_pf_solver::PerturbationSolver solver(
      *this, max_iterations, perturbation_rate, tolerance);
  solver.Solve();
  const auto bus_solutions = solver.GetBusSolutions();
  for (const auto& bus_solution : bus_solutions) {
    bus_solutions_.push_back(bus_solution);
  }
  power_mismatch_perturbation_ = solver.GetPowerMismatchError();
}

/**
 * @brief Solve the power flow problem with Newton-Raphson method and fills
 * bus solutions.
 */
void Network::SolveNewtonRaphson(int max_iterations, double tolerance) {
  newtonraphson_pf_solver::NewtonRaphsonSolver solver(*this, max_iterations,
                                                      tolerance);
  solver.Solve();
  const auto bus_solutions = solver.GetBusSolutions();
  for (const auto& bus_solution : bus_solutions) {
    bus_solutions_.push_back(bus_solution);
  }
  power_mismatch_newtonraphson_ = solver.GetPowerMismatchError();
}

}  // namespace pf_solver