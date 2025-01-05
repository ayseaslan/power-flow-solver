#ifndef TYPES_H_
#define TYPES_H_

#include <complex>
#include <utility>
#include <vector>

namespace pf_solver {
/**
 * @brief Alias for a complex number.
 */
using Complex = std::complex<double>;

/**
 * @brief Alias for a 1D vector of complex numbers.
 */
using Complex1D = std::vector<Complex>;

/**
 * @brief Alias for a vector of integers used for indices.
 */
using IndexVector = std::vector<int>;

/**
 * @brief Alias for a 2D vector of complex numbers.
 */
using Complex2D = std::vector<Complex1D>;

/**
 * @brief Enumeration for the type of bus.
 */
enum class BusType {
  kPQ = 0,    ///< PQ bus type
  kPV,        ///< PV bus type
  kSlack,     ///< Slack/Swing bus type
  kIsolated,  ///< Isolated bus type
};

/**
 * @brief Alias for a pair of double values representing bus given values.
 * For a PQ bus, the first value is the active power and the second value is the
 * reactive power. For a PV bus, the first value is the active power and the
 * second value is the voltage magnitude. For a Slack bus, the first value is
 * the voltage magnitude and the second value is the voltage angle.
 */
using BusGivenValues = std::pair<double, double>;

/**
 * @brief Struct to represent a bus in the power flow network.
 */
struct Bus {
  int bus_id;        ///< The bus ID
  BusType bus_type;  ///< The bus type
  BusGivenValues
      bus_given_values;          ///< The bus given values (e.g. P, Q, V, theta)
  double phase_shift;            ///< The bus phase shift (in radians)
  double voltage_magnitude_max;  ///< The bus voltage magnitude maximum limit
  double voltage_magnitude_min;  ///< The bus voltage magnitude minimum limit

  /**
   * @brief Constructs a Bus object.
   * @param type The bus type.
   * @param bus_given_value_first The first bus given value.
   * @param bus_given_value_second The second bus given value.
   * @param shift The phase shift of the bus.
   * @param voltage_max The maximum voltage magnitude of the bus.
   * @param voltage_min The minimum voltage magnitude of the bus.
   */
  Bus(int id, BusType type, double bus_given_value_first,
      double bus_given_value_second, double shift, double voltage_max,
      double voltage_min)
      : bus_id(id),
        bus_type(type),
        bus_given_values(
            std::make_pair(bus_given_value_first, bus_given_value_second)),
        phase_shift(shift),
        voltage_magnitude_max(voltage_max),
        voltage_magnitude_min(voltage_min) {}
};

/**
 * @brief Struct to represent the detailed solution of a bus in the power flow
 * network.
 */
struct BusSolution {
  int bus_id;                ///< The bus ID
  double voltage_magnitude;  ///< The bus voltage magnitude
  double voltage_angle;      ///< The bus voltage angle
  double active_power;       ///< The bus active power
  double reactive_power;     ///< The bus reactive power

  /**
   * @brief Constructs a BusSolution object.
   * @param id The bus ID.
   * @param magnitude The bus voltage magnitude.
   * @param angle The bus voltage angle.
   * @param p The bus active power.
   * @param q The bus reactive power.
   */
  BusSolution(int id, double magnitude, double angle, double p, double q)
      : bus_id(id),
        voltage_magnitude(magnitude),
        voltage_angle(angle),
        active_power(p),
        reactive_power(q) {}
};

/**
 * @brief Struct to represent the voltage solution of a bus in the power flow
 * network.
 */
struct BusVoltageSolution {
  int bus_id;                ///< The bus ID
  double voltage_magnitude;  ///< The bus voltage magnitude
  double voltage_angle;      ///< The bus voltage angle

  /**
   * @brief Constructs a BusVoltageSolution object.
   * @param id The bus ID.
   * @param magnitude The bus voltage magnitude.
   * @param angle The bus voltage angle.
   */
  BusVoltageSolution(int id, double magnitude, double angle)
      : bus_id(id), voltage_magnitude(magnitude), voltage_angle(angle) {}
};

/**
 * @brief Struct to represent the power solution of a bus in the power flow
 * network.
 */
struct BusPowerSolution {
  int bus_id;             ///< The bus ID
  double active_power;    ///< The bus active power
  double reactive_power;  ///< The bus reactive power

  /**
   * @brief Constructs a BusPowerSolution object.
   * @param id The bus ID.
   * @param active The bus active power.
   * @param reactive The bus reactive power.
   */
  BusPowerSolution(int id, double active, double reactive)
      : bus_id(id), active_power(active), reactive_power(reactive) {}
};

/**
 * @brief Alias for the admittance matrix of the network.
 */
using AdmittanceMatrix = Complex2D;

/**
 * @brief Alias for a vector of buses in the network.
 */
using BusVector = std::vector<Bus>;

/**
 * @brief Alias for a vector of bus solutions.
 */
using BusSolutionVector = std::vector<BusSolution>;

}  // namespace pf_solver
#endif  // TYPES_H_