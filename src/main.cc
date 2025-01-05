#include <iostream>
#include <vector>

#include "cases/fivebus_maple.h"
#include "cases/ieee33.h"
#include "cases/matpower_case141.h"
#include "cases/matpower_case22.h"
#include "cases/matpower_case85.h"
#include "network/network.h"

using namespace pf_solver;
int main() {
  // create a network class instance from cases
  // Network network(cases::fivebus_maple::GetAdmittanceMatrix(),
  //                 cases::fivebus_maple::GetBuses());
  Network network(cases::matpower_case22::GetAdmittanceMatrix(),
                  cases::matpower_case22::GetBuses());
  // Network network(cases::matpower_case85::GetAdmittanceMatrix(),
  //                 cases::matpower_case85::GetBuses());
  // Network network(cases::matpower_case141::GetAdmittanceMatrix(),
  //                 cases::matpower_case141::GetBuses());
  // Network network(cases::ieee33::GetAdmittanceMatrix(),
  //                 cases::ieee33::GetBuses());

  std::cout << "--------------------------------" << std::endl;
  std::cout << "Gauss-Seidel Method" << std::endl;
  network.SolveGaussSeidel(100, 1e-3);
  // network.PrintResults();
  double mismatch_gauss = network.GetPowerMismatchGaussSeidel();
  std::cout << "Gauss-Seidel Power Mismatch: " << mismatch_gauss << std::endl;

  std::cout << "--------------------------------" << std::endl;
  std::cout << "Newton Raphson Method" << std::endl;
  network.SolveNewtonRaphson(100, 1e-3);
  // network.PrintResults();
  double mismatch_newton = network.GetPowerMismatchNewtonRaphson();
  std::cout << "Newton Raphson Power Mismatch: " << mismatch_newton
            << std::endl;

  std::cout << "--------------------------------" << std::endl;
  std::cout << "Gauss-Seidel Perturb Search Algorithm" << std::endl;
  network.SolvePerturbation(100, 0.05, 1e-3);
  // network.PrintResults();
  double mismatch_perturbation = network.GetPowerMismatchPerturbation();
  std::cout << "Perturbation Power Mismatch: " << mismatch_perturbation
            << std::endl;

  std::cout << "--------------------------------" << std::endl;
  std::cout << "Gauss-Seidel Genetic Hybrid Algorithm" << std::endl;
  network.SolveGenetic(20, 0.1, 2, 0.2, 100, 1000, 1e-3);
  // network.PrintResults();
  double mismatch_genetic = network.GetPowerMismatchGenetic();
  std::cout << "Genetic Power Mismatch: " << mismatch_genetic << std::endl;
  return 0;
}
