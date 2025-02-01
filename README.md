# power-flow-solver
Solves power/load flow in single phase networks.

To solve the problem, three methods are implemented: 
- Gauss-Seidel, 
- Newton-Raphson (using power mismatch formulation),
- and a hybrid Genetic algorithm that uses Gauss-Seidel's iteration.

Tests are performed with 5 different load flow instances from the literature. See under include/cases.

