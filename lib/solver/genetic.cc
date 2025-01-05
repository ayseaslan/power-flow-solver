#include "solver/genetic.h"

#include <cmath>
#include <iostream>
#include <ranges>
#include <stdexcept>

namespace genetic_pf_solver {
// static random number generators used for genetic algorithm components
static std::uniform_real_distribution<> dist_uniform(0, 1);
static std::uniform_real_distribution<> dist_small_shift(-0.05, 0.05);
static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<> dist_radians_small(
    -std::numbers::pi / 36, std::numbers::pi / 36);
static std::uniform_real_distribution<> dist_radians(-std::numbers::pi,
                                                     std::numbers::pi);
// used for random solution generation, e.g., initial population

// generates a random voltage magnitude within the given range
double random_voltage_magnitude(double min, double max) {
  static std::uniform_real_distribution<> dis(min, max);
  return dis(gen);
}
// generates a random voltage angle within the range [-pi, pi]
double random_voltage_angle() { return dist_radians(gen); }

// generates a small random shift in voltage magnitude
double random_shift_voltage_magnitude() { return dist_small_shift(gen); }

// generates a small random shift in voltage angle
double random_shift_voltage_angle() { return dist_radians_small(gen); }

void GeneticSolver::FixedChromosomeGenerate(
    ChromosomeVoltage& chromosome) const {
  for (const auto& bus : buses_) {
    if (bus.bus_type == pf_solver::BusType::kSlack) {
      double voltage_magnitude = bus.bus_given_values.first;
      double voltage_angle = bus.bus_given_values.second;
      chromosome.push_back(
          GenesVoltage(bus.bus_id, voltage_magnitude, voltage_angle));
    } else if (bus.bus_type == pf_solver::BusType::kPQ ||
               bus.bus_type == pf_solver::BusType::kIsolated) {
      double voltage_magnitude =
          (bus.voltage_magnitude_max + bus.voltage_magnitude_min) / 2;
      double voltage_angle = bus.phase_shift;
      chromosome.push_back(
          GenesVoltage(bus.bus_id, voltage_magnitude, voltage_angle));
    } else if (bus.bus_type == pf_solver::BusType::kPV) {
      double voltage_magnitude = bus.bus_given_values.second;
      double voltage_angle = bus.phase_shift;
      chromosome.push_back(
          GenesVoltage(bus.bus_id, voltage_magnitude, voltage_angle));
    } else {
      continue;
    }
  }
}

void GeneticSolver::RandomChromosomeGenerate(
    ChromosomeVoltage& chromosome) const {
  // Generate a random chromosome
  for (const auto& bus : buses_) {
    if (bus.bus_type == pf_solver::BusType::kSlack) {
      double voltage_magnitude = bus.bus_given_values.first;
      double voltage_angle = bus.bus_given_values.second;
      chromosome.push_back(
          GenesVoltage(bus.bus_id, voltage_magnitude, voltage_angle));

    } else if (bus.bus_type == pf_solver::BusType::kPQ ||
               bus.bus_type == pf_solver::BusType::kIsolated) {
      double voltage_magnitude = random_voltage_magnitude(
          bus.voltage_magnitude_min, bus.voltage_magnitude_max);
      double voltage_angle = random_voltage_angle();
      chromosome.push_back(
          GenesVoltage(bus.bus_id, voltage_magnitude, voltage_angle));

    } else if (bus.bus_type == pf_solver::BusType::kPV) {
      double voltage_magnitude = bus.bus_given_values.second;
      double voltage_angle = random_voltage_angle();
      chromosome.push_back(
          GenesVoltage(bus.bus_id, voltage_magnitude, voltage_angle));

    } else {
      continue;
    }
  }
}

void GeneticSolver::RandomChromosomeSmallRangeGenerate(
    ChromosomeVoltage& chromosome) const {
  // Generate a random chromosome
  for (const auto& bus : buses_) {
    if (bus.bus_type == pf_solver::BusType::kSlack) {
      double voltage_magnitude = bus.bus_given_values.first;
      double voltage_angle = bus.bus_given_values.second;
      chromosome.push_back(
          GenesVoltage(bus.bus_id, voltage_magnitude, voltage_angle));

    } else if (bus.bus_type == pf_solver::BusType::kPQ ||
               bus.bus_type == pf_solver::BusType::kIsolated) {
      double voltage_magnitude =
          (bus.voltage_magnitude_max + bus.voltage_magnitude_min) / 2;
      double voltage_shift = random_shift_voltage_magnitude();
      if (voltage_magnitude + voltage_shift <= bus.voltage_magnitude_max &&
          voltage_magnitude + voltage_shift >= bus.voltage_magnitude_min) {
        voltage_magnitude += voltage_shift;
      }
      double voltage_angle = bus.phase_shift + random_shift_voltage_angle();
      chromosome.push_back(
          GenesVoltage(bus.bus_id, voltage_magnitude, voltage_angle));

    } else if (bus.bus_type == pf_solver::BusType::kPV) {
      double voltage_magnitude = bus.bus_given_values.second;
      double voltage_angle = bus.phase_shift + random_shift_voltage_angle();
      chromosome.push_back(
          GenesVoltage(bus.bus_id, voltage_magnitude, voltage_angle));

    } else {
      continue;
    }
  }
}

void GeneticSolver::InitializePopulation() {
  // Initialize the population with fixed and random chromosomes
  population_.clear();
  ChromosomeVoltage chromosome;
  FixedChromosomeGenerate(chromosome);
  population_.push_back(chromosome);
  for (int i = 1; i < population_size_; ++i) {
    ChromosomeVoltage chromosome;
    if (i % 2 == 0)
      RandomChromosomeGenerate(chromosome);
    else
      RandomChromosomeSmallRangeGenerate(chromosome);
    population_.push_back(chromosome);
  }
}

void GeneticSolver::ComputePower() {
  // Compute power values for each bus in the population
  population_power_.clear();
  for (const auto& chromosome : population_) {
    ChromosomePower chromosome_power;
    for (const auto& gene : chromosome) {
      double voltage_magnitude = gene.voltage_magnitude;
      double voltage_angle = gene.voltage_angle;
      double active_power = 0.0;
      double reactive_power = 0.0;
      for (const auto& gene_to : chromosome) {
        int bus_from_id = gene.bus_id;
        int bus_to_id = gene_to.bus_id;
        double voltage_magnitude_to = gene_to.voltage_magnitude;
        double voltage_angle_to = gene_to.voltage_angle;
        const auto admittance = admittance_matrix_[bus_from_id][bus_to_id];
        double angle_diff = voltage_angle - voltage_angle_to;
        double real_power = voltage_magnitude * voltage_magnitude_to *
                            (admittance.real() * cos(angle_diff) +
                             admittance.imag() * sin(angle_diff));
        double complex_power = voltage_magnitude * voltage_magnitude_to *
                               (admittance.real() * sin(angle_diff) -
                                admittance.imag() * cos(angle_diff));
        active_power += real_power;
        reactive_power += complex_power;
      }
      chromosome_power.push_back(
          GenesPower(gene.bus_id, active_power, reactive_power));
    }
    population_power_.push_back(chromosome_power);
  }
}

void GeneticSolver::CalculateFitness() {
  // Calculate the fitness of each chromosome in the population
  population_fitness_.clear();
  for (const auto& chromosome : population_power_) {
    double fitness = 0.0;
    int num_p_q_vals = 0;
    for (const auto& gene : chromosome) {
      // Calculate the fitness of the gene based on power mismatch
      int bus_id = gene.bus_id;

      if (buses_[bus_id].bus_type == pf_solver::BusType::kPQ) {
        double active_power = gene.active_power;
        double reactive_power = gene.reactive_power;

        double active_power_given = buses_[bus_id].bus_given_values.first;
        double reactive_power_given = buses_[bus_id].bus_given_values.second;

        fitness += (active_power - active_power_given) *
                   (active_power - active_power_given);
        num_p_q_vals++;
        fitness += (reactive_power - reactive_power_given) *
                   (reactive_power - reactive_power_given);
        num_p_q_vals++;
      } else if (buses_[bus_id].bus_type == pf_solver::BusType::kPV) {
        double active_power = gene.active_power;
        double active_power_given = buses_[bus_id].bus_given_values.second;

        fitness += (active_power - active_power_given) *
                   (active_power - active_power_given);
        num_p_q_vals++;
      } else {
        continue;
      }
    }
    fitness = sqrt(fitness / num_p_q_vals);  // rmse error based fitness
    population_fitness_.push_back(fitness);
  }
}

void GeneticSolver::SelectFittest() {
  // Update the fittest chromosome across the generations
  // with the best solution in the current generation
  if (population_fitness_[0] < fittest_fitness_) {
    fittest_fitness_ = population_fitness_[0];
    fittest_voltage_ = population_[0];
    fittest_power_ = population_power_[0];
  }
}

void GeneticSolver::SortPopulation() {
  // Sort the population based on fitness
  std::vector<std::pair<double, ChromosomeVoltage>> population_and_fitness;
  for (int i = 0; i < population_fitness_.size(); ++i) {
    population_and_fitness.push_back({population_fitness_[i], population_[i]});
  }
  std::sort(population_and_fitness.begin(), population_and_fitness.end(),
            [](const auto& a, const auto& b) { return a.first < b.first; });
  for (int i = 0; i < population_and_fitness.size(); ++i) {
    population_fitness_[i] = population_and_fitness[i].first;
    population_[i] = population_and_fitness[i].second;
  }
}

int GeneticSolver::SelectParent() {
  // Select a parent chromosome based on the tournament selection method
  int parent1 = RandomChromosome();
  int parent2 = RandomChromosome();
  if (parent1 < parent2) {  // since called after sorting
    return parent1;
  } else {
    return parent2;
  }
}

void GeneticSolver::Crossover(const ChromosomeVoltage& parent1,
                              const ChromosomeVoltage& parent2,
                              ChromosomeVoltage& child1,
                              ChromosomeVoltage& child2) {
  // Perform crossover between two parent chromosomes
  int crossover_point = RandomBus();
  for (int i = 0; i < parent1.size(); ++i) {
    if (i < crossover_point) {
      child1.push_back(parent1[i]);
      child2.push_back(parent2[i]);
    } else {
      child1.push_back(parent2[i]);
      child2.push_back(parent1[i]);
    }
  }
}

void GeneticSolver::Mutate(ChromosomeVoltage& chromosome) {
  // Mutate a chromosome by changing the voltage magnitude and angle
  double mutation_time = dist_uniform(gen);
  if (mutation_time < mutation_rate_) {
    int gene_index = RandomBus();
    auto& gene = chromosome[gene_index];
    int bus_id = gene.bus_id;
    if (buses_[bus_id].bus_type == pf_solver::BusType::kPQ) {
      gene.voltage_angle += random_shift_voltage_angle();
      double magnitude_new = random_shift_voltage_magnitude();
      if (gene.voltage_magnitude + magnitude_new <=
              buses_[bus_id].voltage_magnitude_max &&
          gene.voltage_magnitude + magnitude_new >=
              buses_[bus_id].voltage_magnitude_min) {
        gene.voltage_magnitude += magnitude_new;
      }
    }

    if (buses_[bus_id].bus_type == pf_solver::BusType::kPV) {
      gene.voltage_angle += random_shift_voltage_angle();
    }
  }
}

void GeneticSolver::GaussSeidelOneIteration() {
  // Perform Gauss-Seidel method to solve the power flow problem
  // for each bus in the chromosome
  for (auto& chromosome : population_) {
    for (auto& gene : chromosome) {
      int bus_id = gene.bus_id;
      if (buses_[bus_id].bus_type == pf_solver::BusType::kPQ) {
        const auto voltage =
            std::polar(gene.voltage_magnitude, gene.voltage_angle);
        double p = buses_[bus_id].bus_given_values.first;
        double q = buses_[bus_id].bus_given_values.second;
        auto sum = pf_solver::Complex(0, 0);
        for (const auto& gene_to : chromosome) {
          int bus_id_to = gene_to.bus_id;
          if (bus_id != bus_id_to) {
            const auto admittance = admittance_matrix_[bus_id][bus_id_to];
            auto voltage_to =
                std::polar(gene_to.voltage_magnitude, gene_to.voltage_angle);

            sum += voltage_to * admittance;
          }
        }
        auto new_voltage =
            (1.0 / admittance_matrix_[bus_id][bus_id]) *
            ((pf_solver::Complex(p, -q)) / std::conj(voltage) - sum);

        double new_voltage_magnitude = std::abs(new_voltage);
        double new_voltage_angle = std::arg(new_voltage);
        if (new_voltage_magnitude <= buses_[bus_id].voltage_magnitude_max &&
            new_voltage_magnitude >= buses_[bus_id].voltage_magnitude_min) {
          gene.voltage_magnitude = new_voltage_magnitude;
          gene.voltage_angle = new_voltage_angle;
        }
      }
    }
  }
}

void GeneticSolver::Solve() {
  // apply G-S on randomly initialized population
  for (int j = 0; j < gaussseidel_iters_; j++) {
    GaussSeidelOneIteration();
  }
  for (int i = 0; i < max_generations_; ++i) {
    GaussSeidelOneIteration();
    ComputePower();
    CalculateFitness();
    SortPopulation();
    SelectFittest();
    std::cout << "Generation: " << i
              << ", Fittest Fitness: " << fittest_fitness_ << std::endl;
    if (fittest_fitness_ <= tolerance_) {
      std::cout << "Solution found in generation: " << i << std::endl;
      break;
    } else {
      std::vector<ChromosomeVoltage> new_population;
      int added_chromosomes = 0;

      // elitist selection
      while (added_chromosomes < elite_selection_rate_ * population_size_) {
        new_population.push_back(population_[added_chromosomes]);
        added_chromosomes++;
      }
      // also add the fittest solution across generations
      new_population.push_back(fittest_voltage_);
      added_chromosomes++;

      // migration
      for (int j = 0; j < num_migrated_chromosomes_; ++j) {
        if (added_chromosomes < population_size_) {
          ChromosomeVoltage random_chromosome;
          if (added_chromosomes % 2 == 0) {
            RandomChromosomeGenerate(random_chromosome);
          } else {
            RandomChromosomeSmallRangeGenerate(random_chromosome);
          }
          new_population.push_back(random_chromosome);
          added_chromosomes++;
        }
      }

      // crossover and mutation
      while (added_chromosomes < population_size_) {
        int parent1 = SelectParent();
        int parent2 = SelectParent();
        ChromosomeVoltage child1;
        ChromosomeVoltage child2;
        Crossover(population_[parent1], population_[parent2], child1, child2);
        Mutate(child1);
        Mutate(child2);
        new_population.push_back(child1);
        added_chromosomes++;
        new_population.push_back(child2);
        added_chromosomes++;
      }
      population_ = new_population;
    }
  }
}

}  // namespace genetic_pf_solver