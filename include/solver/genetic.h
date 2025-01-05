#ifndef SOLVER_GENETIC_H_
#define SOLVER_GENETIC_H_

#include <numbers>
#include <random>

#include "network/network.h"

namespace genetic_pf_solver {
/**
 * @brief Aliases for the genetic algorithm power flow solver with direct
 * gene encoding using polar voltage representation.
 */
using GenesVoltage = pf_solver::BusVoltageSolution;
using ChromosomeVoltage = std::vector<GenesVoltage>;
using PopulationVoltage = std::vector<ChromosomeVoltage>;

/**
 * @brief Aliases for active and reactive power solutions of the genomes.
 */
using GenesPower = pf_solver::BusPowerSolution;
using ChromosomePower = std::vector<GenesPower>;
using PopulationPower = std::vector<ChromosomePower>;

/**
 * @brief Alias for the population fitness vector.
 */
using PopulationFitness = std::vector<double>;

/**
 * @class GeneticSolver for solving the power flow problem for a given network
 * using the genetic algorithm.
 */
class GeneticSolver {
 public:
  /**
   * @brief Constructs a GeneticSolver object.
   * @param network The power flow network instance.
   * @param population_size The size of the population.
   * @param mutation_rate The mutation rate.
   * @param migrations The number of chromosomes to migrate.
   * @param elite_selection_rate The elite selection rate.
   * @param gaussseidel_iters The number of Gauss-Seidel iterations to apply to
   * initial population.
   * @param max_generations The maximum number of generations.
   * @param tolerance The convergence tolerance.
   */
  GeneticSolver(const pf_solver::Network& network, int population_size = 10,
                double mutation_rate = 0.1, int migrations = 1,
                double elite_selection_rate = 0.1, int gaussseidel_iters = 100,
                int max_generations = 100, double tolerance = 1e-3)
      : population_size_(population_size),
        mutation_rate_(mutation_rate),
        max_generations_(max_generations),
        elite_selection_rate_(elite_selection_rate),
        num_migrated_chromosomes_(migrations),
        admittance_matrix_(network.GetAdmittanceMatrix()),
        buses_(network.GetBuses()),
        num_buses_(network.GetNumBuses()),
        gaussseidel_iters_(gaussseidel_iters),
        tolerance_(tolerance),
        engine(std::random_device{}()),
        dist_bus(0, num_buses_ - 1),
        dist_population(0, population_size - 1) {
    InitializePopulation();
    fittest_fitness_ = std::numeric_limits<double>::max();
  }

  /**
   * @brief Destructor for the GeneticSolver class.
   */
  ~GeneticSolver() = default;

  /**
   * @brief Solve the power flow problem using the genetic algorithm.
   */
  void Solve();

  /**
   * @brief Get the bus voltage solution.
   * @return The bus voltage solution.
   */
  ChromosomeVoltage GetBusVoltageSolution() const { return fittest_voltage_; }

  /**
   * @brief Get the bus power solution.
   * @return The bus power solution.
   */
  ChromosomePower GetBusPowerSolution() const { return fittest_power_; }

  /**
   * @brief Get the error in the power flow solution.
   * @return The error in the power flow solution.
   */
  double GetPowerMismatchError() const { return fittest_fitness_; }

 private:
  PopulationVoltage population_;      ///< The population of chromosomes.
  PopulationPower population_power_;  ///< The power values of the population.

  PopulationFitness population_fitness_;  ///< The fitness of the population.
  ChromosomeVoltage fittest_voltage_;     ///< The fittest chromosome.
  ChromosomePower fittest_power_;         ///< The power values of the fittest.
  double fittest_fitness_;  ///< The fitness of the fittest chromosome.

  int population_size_;          ///< The size of the population.
  double mutation_rate_;         ///< The mutation rate.
  double migration_rate_;        ///< The migration rate.
  double elite_selection_rate_;  ///< The elite selection rate.
  int gaussseidel_iters_;  ///< The number of Gauss-Seidel iterations to apply
                           ///< on the initial population.
  int num_migrated_chromosomes_;  ///< The number of chromosomes to migrate.
  int max_generations_;           ///< The maximum number of generations.
  double tolerance_;              ///< The convergence tolerance.

  pf_solver::AdmittanceMatrix admittance_matrix_;  ///< The admittance matrix.
  pf_solver::BusVector buses_;  ///< The list of buses in the network.
  int num_buses_;               ///< The number of buses in the network.

  /**
   * @brief Generates a fixed chromosome for voltage solutions.
   */
  void FixedChromosomeGenerate(ChromosomeVoltage& chromosome) const;

  /**
   * @brief Generates a random chromosome for voltage solutions considering the
   * entire range of possible values.
   */
  void RandomChromosomeGenerate(ChromosomeVoltage& chromosome) const;

  /**
   * @brief Generates a random chromosome for voltage solutions considering a
   * small range of possible values.
   */
  void RandomChromosomeSmallRangeGenerate(ChromosomeVoltage& chromosome) const;

  /**
   * @brief Applies one iteration of the Gauss-Seidel method on the population.
   */
  void GaussSeidelOneIteration();

  /**
   * @brief Initializes the population with fixed and random chromosomes.
   */
  void InitializePopulation();

  /**
   * @brief Computes power values for each bus in the population.
   */
  void ComputePower();

  /**
   * @brief Calculates the fitness of each chromosome in the population.
   */
  void CalculateFitness();

  /**
   * @brief Selects the fittest chromosome in the population.
   */
  void SelectFittest();

  /**
   * @brief Applies the crossover operation on the given two parents to produce
   * two children.
   */
  void Crossover(const ChromosomeVoltage& parent1,
                 const ChromosomeVoltage& parent2, ChromosomeVoltage& child1,
                 ChromosomeVoltage& child2);

  /**
   * @brief Mutates a chromosome by changing the voltage magnitude and angle.
   */
  void Mutate(ChromosomeVoltage& chromosome);

  /**
   * @brief Selects a parent chromosome from the population for crossover.
   */
  int SelectParent();

  /**
   * @brief Sorts the population based on fitness values.
   */
  void SortPopulation();

  /**
   * @brief Selects a random bus from the network.
   */
  int RandomBus() { return dist_bus(engine); }

  /**
   * @brief Selects a random chromosome from the population.
   */
  int RandomChromosome() { return dist_population(engine); }

  std::uniform_int_distribution<>
      dist_bus;  // Distribution for random bus selection
  std::uniform_int_distribution<>
      dist_population;  // Distribution for random chromosome selection
  std::mt19937 engine;  // Random number engine
};

}  // namespace genetic_pf_solver
#endif  // SOLVER_GENETIC_H_