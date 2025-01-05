#include "solver/perturbation.h"

#include <iostream>
#include <numbers>
#include <random>

namespace perturbation_pf_solver {
// Static random number generators used for perturbation step
static std::uniform_real_distribution<> dist_uniform(0, 1);
static std::uniform_real_distribution<> dist_small_shift(
    -0.02, 0.02);  // 2% p.u. neighborhood
static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<> dist_radians_small(
    -std::numbers::pi / 180, std::numbers::pi / 180);  // 2 degree neighborhood

void PerturbationSolver::Solve() {
  // Solve the power flow problem using the perturb and search method
  // Initialize the bus solutions
  bus_solutions_.clear();
  for (const auto& bus : buses_) {
    if (bus.bus_type == pf_solver::BusType::kSlack) {
      double voltage_magnitude = bus.bus_given_values.first;
      double voltage_angle = bus.bus_given_values.second;
      bus_solutions_.push_back(pf_solver::BusSolution(
          bus.bus_id, voltage_magnitude, voltage_angle, 0, 0));
    } else if (bus.bus_type == pf_solver::BusType::kPQ ||
               bus.bus_type == pf_solver::BusType::kIsolated) {
      double voltage_magnitude =
          (bus.voltage_magnitude_max + bus.voltage_magnitude_min) / 2;
      double voltage_angle = bus.phase_shift;
      bus_solutions_.push_back(pf_solver::BusSolution(
          bus.bus_id, voltage_magnitude, voltage_angle, 0, 0));
    } else if (bus.bus_type == pf_solver::BusType::kPV) {
      double voltage_magnitude = bus.bus_given_values.second;
      double voltage_angle = bus.phase_shift;
      bus_solutions_.push_back(pf_solver::BusSolution(
          bus.bus_id, voltage_magnitude, voltage_angle, 0, 0));
    } else {
      continue;
    }
  }

  // Perform the perturb and search method
  for (int i = 0; i < max_iterations_; ++i) {
    // G-S step
    for (auto& bus : bus_solutions_) {
      int bus_id = bus.bus_id;
      if (buses_[bus_id].bus_type == pf_solver::BusType::kPQ) {
        const auto voltage =
            std::polar(bus.voltage_magnitude, bus.voltage_angle);
        double p = buses_[bus_id].bus_given_values.first;
        double q = buses_[bus_id].bus_given_values.second;
        auto sum = pf_solver::Complex(0, 0);
        for (const auto& bus_to : bus_solutions_) {
          int bus_id_to = bus_to.bus_id;
          if (bus_id != bus_id_to) {
            const auto admittance = admittance_matrix_[bus_id][bus_id_to];
            const auto voltage_to =
                std::polar(bus_to.voltage_magnitude, bus_to.voltage_angle);

            sum += voltage_to * admittance;
          }
        }
        const auto new_voltage =
            (1.0 / admittance_matrix_[bus_id][bus_id]) *
            ((pf_solver::Complex(p, -q)) / std::conj(voltage) - sum);

        double new_voltage_magnitude = std::abs(new_voltage);
        double new_voltage_angle = std::arg(new_voltage);
        if (new_voltage_magnitude <= buses_[bus_id].voltage_magnitude_max &&
            new_voltage_magnitude >= buses_[bus_id].voltage_magnitude_min) {
          bus.voltage_magnitude = new_voltage_magnitude;
          bus.voltage_angle = new_voltage_angle;
        }
      }
    }
    // Compute power
    for (auto& bus : bus_solutions_) {
      int bus_id = bus.bus_id;
      double active_power = 0.0;
      double reactive_power = 0.0;
      for (const auto& bus_to : bus_solutions_) {
        int bus_id_to = bus_to.bus_id;
        double voltage_magnitude_to = bus_to.voltage_magnitude;
        double voltage_angle_to = bus_to.voltage_angle;
        const auto admittance = admittance_matrix_[bus_id][bus_id_to];
        double angle_diff = bus.voltage_angle - voltage_angle_to;
        double real_power = bus.voltage_magnitude * voltage_magnitude_to *
                            (admittance.real() * cos(angle_diff) +
                             admittance.imag() * sin(angle_diff));
        double complex_power = bus.voltage_magnitude * voltage_magnitude_to *
                               (admittance.real() * sin(angle_diff) -
                                admittance.imag() * cos(angle_diff));
        active_power += real_power;
        reactive_power += complex_power;
      }
      bus.active_power = active_power;
      bus.reactive_power = reactive_power;
    }
    // Compute the power mismatch
    double total_power_mismatch = 0.0;
    int num_p_q_vals = 0;
    int max_mismatch_bus_id = -1;
    double max_mismatch = 0.0;
    for (const auto& bus : bus_solutions_) {
      int bus_id = bus.bus_id;
      if (buses_[bus_id].bus_type == pf_solver::BusType::kPQ) {
        double active_power = bus.active_power;
        double reactive_power = bus.reactive_power;

        double active_power_given = buses_[bus_id].bus_given_values.first;
        double reactive_power_given = buses_[bus_id].bus_given_values.second;

        double mismatch_active = (active_power - active_power_given) *
                                 (active_power - active_power_given);
        double mismatch_reactive = (reactive_power - reactive_power_given) *
                                   (reactive_power - reactive_power_given);

        total_power_mismatch += mismatch_active;
        total_power_mismatch += mismatch_reactive;
        num_p_q_vals += 2;
        if (mismatch_active + mismatch_reactive > max_mismatch) {
          max_mismatch = mismatch_active + mismatch_reactive;
          max_mismatch_bus_id = bus_id;
        }
      } else if (buses_[bus_id].bus_type == pf_solver::BusType::kPV) {
        double active_power = bus.active_power;
        double active_power_given = buses_[bus_id].bus_given_values.second;
        double mismatch_active = (active_power - active_power_given) *
                                 (active_power - active_power_given);
        total_power_mismatch += mismatch_active;
        num_p_q_vals++;
        if (mismatch_active > max_mismatch) {
          max_mismatch = mismatch_active;
          max_mismatch_bus_id = bus_id;
        }
      } else {
        continue;
      }
    }
    power_mismatch_ = sqrt(total_power_mismatch / num_p_q_vals);
    // Log the power mismatch
    std::cout << "Iteration: " << i
              << ", Total Power Mismatch: " << power_mismatch_ << std::endl;
    if (power_mismatch_ <= tolerance_) {
      break;
    }
    // Perturb the voltage solutions by random small values
    double perturbation_chance = dist_uniform(gen);
    if (perturbation_chance < perturbation_rate_) {
      int bus_id_perturb = max_mismatch_bus_id;
      auto& bus = bus_solutions_[bus_id_perturb];
      if (buses_[bus_id_perturb].bus_type == pf_solver::BusType::kPQ) {
        double voltage_shift = dist_small_shift(gen);
        if (bus.voltage_magnitude + voltage_shift >
            buses_[bus_id_perturb].voltage_magnitude_max) {
          bus.voltage_magnitude = buses_[bus_id_perturb].voltage_magnitude_max;
        } else if (bus.voltage_magnitude + voltage_shift <
                   buses_[bus_id_perturb].voltage_magnitude_min) {
          bus.voltage_magnitude = buses_[bus_id_perturb].voltage_magnitude_min;
        } else {
          bus.voltage_magnitude += voltage_shift;
        }
        bus.voltage_angle += dist_radians_small(gen);
      }
      if (buses_[bus_id_perturb].bus_type == pf_solver::BusType::kPV) {
        bus.voltage_angle += dist_radians_small(gen);
      }
    }
  }
}

}  // namespace perturbation_pf_solver