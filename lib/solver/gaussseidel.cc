#include "solver/gaussseidel.h"

#include <iostream>

namespace gauss_seidel_pf_solver {
void GaussSeidelSolver::Solve() {
  // Generate an initial guess for the bus voltages and angles
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

  for (int i = 0; i < max_iterations_; ++i) {
    // update the bus voltages and angles
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
    // compute power
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
    for (const auto& bus : bus_solutions_) {
      int bus_id = bus.bus_id;
      if (buses_[bus_id].bus_type == pf_solver::BusType::kPQ) {
        double active_power = bus.active_power;
        double reactive_power = bus.reactive_power;
        double active_power_given = buses_[bus_id].bus_given_values.first;
        double reactive_power_given = buses_[bus_id].bus_given_values.second;
        double mismatch_active = (active_power - active_power_given) *
                                 (active_power - active_power_given);
        total_power_mismatch += mismatch_active;
        num_p_q_vals++;
        double mismatch_reactive = (reactive_power - reactive_power_given) *
                                   (reactive_power - reactive_power_given);
        num_p_q_vals++;
        total_power_mismatch += mismatch_reactive;
      } else if (buses_[bus_id].bus_type == pf_solver::BusType::kPV) {
        double active_power = bus.active_power;
        double active_power_given = buses_[bus_id].bus_given_values.second;
        double mismatch_active = (active_power - active_power_given) *
                                 (active_power - active_power_given);
        total_power_mismatch += mismatch_active;
        num_p_q_vals++;
      } else {
        continue;
      }
    }
    total_power_mismatch =
        sqrt(total_power_mismatch / num_p_q_vals);  // rmse error based mismatch
    power_mismatch_ = total_power_mismatch;
    // Log the power mismatch
    std::cout << "Iteration: " << i
              << ", Total Power Mismatch: " << total_power_mismatch
              << std::endl;
    // Stop if the power mismatch is below the tolerance
    if (power_mismatch_ < tolerance_) {
      std::cout << "Converged after " << i << " iterations." << std::endl;
      break;
    }
  }
}
}  // namespace gauss_seidel_pf_solver