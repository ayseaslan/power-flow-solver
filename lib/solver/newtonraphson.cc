#include "solver/newtonraphson.h"

#include <Eigen/Dense>
#include <iostream>
#include <numbers>

using namespace Eigen;
namespace newtonraphson_pf_solver {

void NewtonRaphsonSolver::AssignNonPQBusIds() {
  for (const auto& bus : buses_) {
    if (bus.bus_type == pf_solver::BusType::kSlack) {
      slack_buses_.push_back(bus.bus_id);
    }
    if (bus.bus_type == pf_solver::BusType::kPV) {
      pv_buses_.push_back(bus.bus_id);
    }
    if (bus.bus_type == pf_solver::BusType::kIsolated) {
      isolated_buses_.push_back(bus.bus_id);
    }
  }
}

bool NewtonRaphsonSolver::ValidAngle(double angle) const {
  return angle >= -std::numbers::pi && angle <= std::numbers::pi;
}

bool NewtonRaphsonSolver::ValidMagnitude(double magnitude, int bus_id) const {
  return magnitude >= buses_[bus_id].voltage_magnitude_min &&
         magnitude <= buses_[bus_id].voltage_magnitude_max;
}

int NewtonRaphsonSolver::SolveWithJacobian() {
  // Construct the Jacobian matrix for the Newton-Raphson method
  MatrixXd J(2 * num_buses_, 2 * num_buses_);
  VectorXd mismatch(2 * num_buses_);
  J.setZero();
  for (const auto& bus : bus_solutions_) {
    for (const auto& bus_to : bus_solutions_) {
      int i = bus.bus_id;
      int j = bus_to.bus_id;
      double Gij = real(admittance_matrix_[i][j]);
      double Bij = imag(admittance_matrix_[i][j]);
      double angle_diff = bus.voltage_angle - bus_to.voltage_angle;

      if (i == j) {
        // Diagonal elements of the Jacobian matrix
        double Pi = 0.0, Qi = 0.0;
        for (const auto& bus_diag : bus_solutions_) {
          int k = bus_diag.bus_id;
          if (k != i) {
            double Gik = real(admittance_matrix_[i][k]);
            double Bik = imag(admittance_matrix_[i][k]);
            double angle_diff_k = bus.voltage_angle - bus_diag.voltage_angle;
            Pi += bus_diag.voltage_magnitude *
                  (Gik * cos(angle_diff_k) + Bik * sin(angle_diff_k));
            Qi += bus_diag.voltage_magnitude *
                  (Gik * sin(angle_diff_k) - Bik * cos(angle_diff_k));
          }
        }
        J(i, i) = bus.voltage_magnitude * Qi;
        J(i, i + num_buses_) = -2.0 * Gij * bus.voltage_magnitude - Pi;
        J(i + num_buses_, i) = -bus.voltage_magnitude * Pi;
        J(i + num_buses_, i + num_buses_) =
            2.0 * Bij * bus.voltage_magnitude - Qi;

      } else {
        // Off-diagonal elements of the Jacobian matrix
        J(i, j) = -1.0 * bus.voltage_magnitude * bus_to.voltage_magnitude *
                  (Gij * sin(angle_diff) - Bij * cos(angle_diff));
        J(i, j + num_buses_) = -1.0 * bus.voltage_magnitude *
                               (Gij * cos(angle_diff) + Bij * sin(angle_diff));
        J(i + num_buses_, j) = bus.voltage_magnitude *
                               bus_to.voltage_magnitude *
                               (Gij * cos(angle_diff) + Bij * sin(angle_diff));
        J(i + num_buses_, j + num_buses_) =
            -1.0 * bus.voltage_magnitude *
            (Gij * sin(angle_diff) - Bij * cos(angle_diff));
      }
    }
  }
  // handle slack buses
  for (const auto& slack_idx : slack_buses_) {
    // Zero out rows and columns of the slack bus
    J.row(slack_idx).setZero();
    J.col(slack_idx).setZero();
    J.row(slack_idx + num_buses_).setZero();
    J.col(slack_idx + num_buses_).setZero();
    J(slack_idx, slack_idx) = 1.0;  // Set diagonal to 1 for numerical stability
  }
  // handle isolated buses
  for (const auto& isolated_idx : isolated_buses_) {
    // Zero out rows and columns of the isolated bus
    J.row(isolated_idx).setZero();
    J.col(isolated_idx).setZero();
    J.row(isolated_idx + num_buses_).setZero();
    J.col(isolated_idx + num_buses_).setZero();
    J(isolated_idx, isolated_idx) =
        1.0;  // Set diagonal for numerical stability
  }
  // handle PV buses
  for (const auto& pv_idx : pv_buses_) {
    // Zero out rows and columns of the PV bus
    J.row(pv_idx + num_buses_).setZero();  // corresponding to Q
    J.col(pv_idx + num_buses_).setZero();  // corresponding to V magnitude
    J(pv_idx + num_buses_, pv_idx + num_buses_) =
        1.0;  // Set diagonal for numerical stability
  }
  // compute mismatch for p and q values
  double total_power_mismatch = 0.0;
  int num_p_q_vals = 0;
  for (const auto& bus : bus_solutions_) {
    int i = bus.bus_id;
    double p_computed = 0.0, q_computed = 0.0;
    double p_mismatch = 0.0, q_mismatch = 0.0;
    for (const auto& bus_to : bus_solutions_) {
      int j = bus_to.bus_id;
      double Gij = real(admittance_matrix_[i][j]);
      double Bij = imag(admittance_matrix_[i][j]);
      double angle_diff = bus.voltage_angle - bus_to.voltage_angle;
      p_computed += bus.voltage_magnitude * bus_to.voltage_magnitude *
                    (Gij * cos(angle_diff) + Bij * sin(angle_diff));
      q_computed += bus.voltage_magnitude * bus_to.voltage_magnitude *
                    (Gij * sin(angle_diff) - Bij * cos(angle_diff));
    }
    // Update the power solutions
    bus_solutions_[i].active_power = p_computed;
    bus_solutions_[i].reactive_power = q_computed;

    if (buses_[i].bus_type == pf_solver::BusType::kPQ) {
      p_mismatch = buses_[i].bus_given_values.first - p_computed;
      q_mismatch = buses_[i].bus_given_values.second - q_computed;
      num_p_q_vals += 2;
    }
    if (buses_[i].bus_type == pf_solver::BusType::kPV) {
      p_mismatch = buses_[i].bus_given_values.first - p_computed;
      num_p_q_vals++;
    }
    mismatch(i) = p_mismatch;
    mismatch(i + num_buses_) = q_mismatch;
    total_power_mismatch += p_mismatch * p_mismatch + q_mismatch * q_mismatch;
  }
  // check for convergence
  power_mismatch_ = std::sqrt(total_power_mismatch / num_p_q_vals);
  if (power_mismatch_ < tolerance_) {
    return 1;
  } else {
    // Solve for the updates
    VectorXd dx = -J.colPivHouseholderQr().solve(mismatch);
    for (int i = 0; i < num_buses_; ++i) {
      if (buses_[i].bus_type == pf_solver::BusType::kPQ ||
          buses_[i].bus_type == pf_solver::BusType::kPV) {
        if (ValidAngle(bus_solutions_[i].voltage_angle + dx(i))) {
          bus_solutions_[i].voltage_angle += dx(i);
        }
        if (buses_[i].bus_type == pf_solver::BusType::kPQ)
          if (ValidMagnitude(
                  bus_solutions_[i].voltage_magnitude + dx(i + num_buses_),
                  i)) {
            bus_solutions_[i].voltage_magnitude += dx(i + num_buses_);
          }
      }
    }
    return 0;
  }
}

void NewtonRaphsonSolver::Solve() {
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
  // Perform the Newton-Raphson method
  int iter = 0;
  while (iter < max_iterations_) {
    if (SolveWithJacobian() == 1) {
      break;
    }
    iter++;
  }
}
}  // namespace newtonraphson_pf_solver