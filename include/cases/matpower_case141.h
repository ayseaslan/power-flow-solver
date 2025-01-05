#ifndef CASES_MATPOWER_CASE141_H_
#define CASES_MATPOWER_CASE141_H_

#include "matpower.h"

namespace pf_solver {
namespace cases {
namespace matpower_case141 {
// See https://github.com/MATPOWER/matpower/blob/master/data/case141.m

// use per unit base values for per unit conversions
const double base_mva = 10.0;
const double base_kv = 12.47;
const double base_v = 1e3 * base_kv;   // kV to V
const double base_s = 1e6 * base_mva;  // MVA to VA
const double base_z = base_v * base_v / base_s;

Bus slack = Bus(0, BusType::kSlack, 1, 0, 0, 1.0, 1.0);
Bus PQ2 = Bus(1, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ3 = Bus(2, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ4 = Bus(3, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ5 = Bus(4, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ6 = Bus(5, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ7 = Bus(6, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ8 = Bus(7, BusType::kPQ, -75, 0, 0, 1.1, 0.9);
Bus PQ9 = Bus(8, BusType::kPQ, -10, 0, 0, 1.1, 0.9);
Bus PQ10 = Bus(9, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ11 = Bus(10, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ12 = Bus(11, BusType::kPQ, -25, 0, 0, 1.1, 0.9);
Bus PQ13 = Bus(12, BusType::kPQ, -75, 0, 0, 1.1, 0.9);
Bus PQ14 = Bus(13, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ15 = Bus(14, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ16 = Bus(15, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ17 = Bus(16, BusType::kPQ, -150, 0, 0, 1.1, 0.9);
Bus PQ18 = Bus(17, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ19 = Bus(18, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ20 = Bus(19, BusType::kPQ, -75, 0, 0, 1.1, 0.9);
Bus PQ21 = Bus(20, BusType::kPQ, -75, 0, 0, 1.1, 0.9);
Bus PQ22 = Bus(21, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ23 = Bus(22, BusType::kPQ, -75, 0, 0, 1.1, 0.9);
Bus PQ24 = Bus(23, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ25 = Bus(24, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ26 = Bus(25, BusType::kPQ, -150, 0, 0, 1.1, 0.9);
Bus PQ27 = Bus(26, BusType::kPQ, -75, 0, 0, 1.1, 0.9);
Bus PQ28 = Bus(27, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ29 = Bus(28, BusType::kPQ, -75, 0, 0, 1.1, 0.9);
Bus PQ30 = Bus(29, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ31 = Bus(30, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ32 = Bus(31, BusType::kPQ, -150, 0, 0, 1.1, 0.9);
Bus PQ33 = Bus(32, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ34 = Bus(33, BusType::kPQ, -150, 0, 0, 1.1, 0.9);
Bus PQ35 = Bus(34, BusType::kPQ, -300, 0, 0, 1.1, 0.9);
Bus PQ36 = Bus(35, BusType::kPQ, -150, 0, 0, 1.1, 0.9);
Bus PQ37 = Bus(36, BusType::kPQ, -50, 0, 0, 1.1, 0.9);
Bus PQ38 = Bus(37, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ39 = Bus(38, BusType::kPQ, -20, 0, 0, 1.1, 0.9);
Bus PQ40 = Bus(39, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ41 = Bus(40, BusType::kPQ, -75, 0, 0, 1.1, 0.9);
Bus PQ42 = Bus(41, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ43 = Bus(42, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ44 = Bus(43, BusType::kPQ, -50, 0, 0, 1.1, 0.9);
Bus PQ45 = Bus(44, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ46 = Bus(45, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ47 = Bus(46, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ48 = Bus(47, BusType::kPQ, -125, 0, 0, 1.1, 0.9);
Bus PQ49 = Bus(48, BusType::kPQ, -150, 0, 0, 1.1, 0.9);
Bus PQ50 = Bus(49, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ51 = Bus(50, BusType::kPQ, -125, 0, 0, 1.1, 0.9);
Bus PQ52 = Bus(51, BusType::kPQ, -75, 0, 0, 1.1, 0.9);
Bus PQ53 = Bus(52, BusType::kPQ, -100, 0, 0, 1.1, 0.9);
Bus PQ54 = Bus(53, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ55 = Bus(54, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ56 = Bus(55, BusType::kPQ, -25, 0, 0, 1.1, 0.9);
Bus PQ57 = Bus(56, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ58 = Bus(57, BusType::kPQ, -300, 0, 0, 1.1, 0.9);
Bus PQ59 = Bus(58, BusType::kPQ, -150, 0, 0, 1.1, 0.9);
Bus PQ60 = Bus(59, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ61 = Bus(60, BusType::kPQ, -300, 0, 0, 1.1, 0.9);
Bus PQ62 = Bus(61, BusType::kPQ, -200, 0, 0, 1.1, 0.9);
Bus PQ63 = Bus(62, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ64 = Bus(63, BusType::kPQ, -300, 0, 0, 1.1, 0.9);
Bus PQ65 = Bus(64, BusType::kPQ, -150, 0, 0, 1.1, 0.9);
Bus PQ66 = Bus(65, BusType::kPQ, -225, 0, 0, 1.1, 0.9);
Bus PQ67 = Bus(66, BusType::kPQ, -50, 0, 0, 1.1, 0.9);
Bus PQ68 = Bus(67, BusType::kPQ, -100, 0, 0, 1.1, 0.9);
Bus PQ69 = Bus(68, BusType::kPQ, -300, 0, 0, 1.1, 0.9);
Bus PQ70 = Bus(69, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ71 = Bus(70, BusType::kPQ, -300, 0, 0, 1.1, 0.9);
Bus PQ72 = Bus(71, BusType::kPQ, -150, 0, 0, 1.1, 0.9);
Bus PQ73 = Bus(72, BusType::kPQ, -300, 0, 0, 1.1, 0.9);
Bus PQ74 = Bus(73, BusType::kPQ, -300, 0, 0, 1.1, 0.9);
Bus PQ75 = Bus(74, BusType::kPQ, -45, 0, 0, 1.1, 0.9);
Bus PQ76 = Bus(75, BusType::kPQ, -75, 0, 0, 1.1, 0.9);
Bus PQ77 = Bus(76, BusType::kPQ, -150, 0, 0, 1.1, 0.9);
Bus PQ78 = Bus(77, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ79 = Bus(78, BusType::kPQ, -502.5, 0, 0, 1.1, 0.9);
Bus PQ80 = Bus(79, BusType::kPQ, -750, 0, 0, 1.1, 0.9);
Bus PQ81 = Bus(80, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ82 = Bus(81, BusType::kPQ, -150, 0, 0, 1.1, 0.9);
Bus PQ83 = Bus(82, BusType::kPQ, -75, 0, 0, 1.1, 0.9);
Bus PQ84 = Bus(83, BusType::kPQ, -225, 0, 0, 1.1, 0.9);
Bus PQ85 = Bus(84, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ86 = Bus(85, BusType::kPQ, -500, 0, 0, 1.1, 0.9);
Bus PQ87 = Bus(86, BusType::kPQ, -150, 0, 0, 1.1, 0.9);
Bus PQ88 = Bus(87, BusType::kPQ, -75, 0, 0, 1.1, 0.9);
Bus PQ89 = Bus(88, BusType::kPQ, -65, 0, 0, 1.1, 0.9);
Bus PQ90 = Bus(89, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ91 = Bus(90, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ92 = Bus(91, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ93 = Bus(92, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ94 = Bus(93, BusType::kPQ, -110, 0, 0, 1.1, 0.9);
Bus PQ95 = Bus(94, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ96 = Bus(95, BusType::kPQ, -150, 0, 0, 1.1, 0.9);
Bus PQ97 = Bus(96, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ98 = Bus(97, BusType::kPQ, -300, 0, 0, 1.1, 0.9);
Bus PQ99 = Bus(98, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ100 = Bus(99, BusType::kPQ, -300, 0, 0, 1.1, 0.9);
Bus PQ101 = Bus(100, BusType::kPQ, -15, 0, 0, 1.1, 0.9);
Bus PQ102 = Bus(101, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ103 = Bus(102, BusType::kPQ, -125, 0, 0, 1.1, 0.9);
Bus PQ104 = Bus(103, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ105 = Bus(104, BusType::kPQ, -300, 0, 0, 1.1, 0.9);
Bus PQ106 = Bus(105, BusType::kPQ, -150, 0, 0, 1.1, 0.9);
Bus PQ107 = Bus(106, BusType::kPQ, -502.5, 0, 0, 1.1, 0.9);
Bus PQ108 = Bus(107, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ109 = Bus(108, BusType::kPQ, -750, 0, 0, 1.1, 0.9);
Bus PQ110 = Bus(109, BusType::kPQ, -750, 0, 0, 1.1, 0.9);
Bus PQ111 = Bus(110, BusType::kPQ, -25, 0, 0, 1.1, 0.9);
Bus PQ112 = Bus(111, BusType::kPQ, -500, 0, 0, 1.1, 0.9);
Bus PQ113 = Bus(112, BusType::kPQ, -75, 0, 0, 1.1, 0.9);
Bus PQ114 = Bus(113, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ115 = Bus(114, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ116 = Bus(115, BusType::kPQ, -300, 0, 0, 1.1, 0.9);
Bus PQ117 = Bus(116, BusType::kPQ, -65, 0, 0, 1.1, 0.9);
Bus PQ118 = Bus(117, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ119 = Bus(118, BusType::kPQ, -110, 0, 0, 1.1, 0.9);
Bus PQ120 = Bus(119, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ121 = Bus(120, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ122 = Bus(121, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ123 = Bus(122, BusType::kPQ, -100, 0, 0, 1.1, 0.9);
Bus PQ124 = Bus(123, BusType::kPQ, -125, 0, 0, 1.1, 0.9);
Bus PQ125 = Bus(124, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ126 = Bus(125, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ127 = Bus(126, BusType::kPQ, -75, 0, 0, 1.1, 0.9);
Bus PQ128 = Bus(127, BusType::kPQ, -75, 0, 0, 1.1, 0.9);
Bus PQ129 = Bus(128, BusType::kPQ, -110, 0, 0, 1.1, 0.9);
Bus PQ130 = Bus(129, BusType::kPQ, -112.5, 0, 0, 1.1, 0.9);
Bus PQ131 = Bus(130, BusType::kIsolated, 0, 0, 0, 1.1, 0.9);
Bus PQ132 = Bus(131, BusType::kPQ, -75, 0, 0, 1.1, 0.9);
Bus PQ133 = Bus(132, BusType::kPQ, -45, 0, 0, 1.1, 0.9);
Bus PQ134 = Bus(133, BusType::kPQ, -35, 0, 0, 1.1, 0.9);
Bus PQ135 = Bus(134, BusType::kPQ, -25, 0, 0, 1.1, 0.9);
Bus PQ136 = Bus(135, BusType::kPQ, -75, 0, 0, 1.1, 0.9);
Bus PQ137 = Bus(136, BusType::kPQ, -55, 0, 0, 1.1, 0.9);
Bus PQ138 = Bus(137, BusType::kPQ, -50, 0, 0, 1.1, 0.9);
Bus PQ139 = Bus(138, BusType::kPQ, -50, 0, 0, 1.1, 0.9);
Bus PQ140 = Bus(139, BusType::kPQ, -150, 0, 0, 1.1, 0.9);
Bus PQ141 = Bus(140, BusType::kPQ, -75, 0, 0, 1.1, 0.9);

BusVector buses = {
    slack, PQ2,   PQ3,   PQ4,   PQ5,   PQ6,   PQ7,   PQ8,   PQ9,   PQ10,  PQ11,
    PQ12,  PQ13,  PQ14,  PQ15,  PQ16,  PQ17,  PQ18,  PQ19,  PQ20,  PQ21,  PQ22,
    PQ23,  PQ24,  PQ25,  PQ26,  PQ27,  PQ28,  PQ29,  PQ30,  PQ31,  PQ32,  PQ33,
    PQ34,  PQ35,  PQ36,  PQ37,  PQ38,  PQ39,  PQ40,  PQ41,  PQ42,  PQ43,  PQ44,
    PQ45,  PQ46,  PQ47,  PQ48,  PQ49,  PQ50,  PQ51,  PQ52,  PQ53,  PQ54,  PQ55,
    PQ56,  PQ57,  PQ58,  PQ59,  PQ60,  PQ61,  PQ62,  PQ63,  PQ64,  PQ65,  PQ66,
    PQ67,  PQ68,  PQ69,  PQ70,  PQ71,  PQ72,  PQ73,  PQ74,  PQ75,  PQ76,  PQ77,
    PQ78,  PQ79,  PQ80,  PQ81,  PQ82,  PQ83,  PQ84,  PQ85,  PQ86,  PQ87,  PQ88,
    PQ89,  PQ90,  PQ91,  PQ92,  PQ93,  PQ94,  PQ95,  PQ96,  PQ97,  PQ98,  PQ99,
    PQ100, PQ101, PQ102, PQ103, PQ104, PQ105, PQ106, PQ107, PQ108, PQ109, PQ110,
    PQ111, PQ112, PQ113, PQ114, PQ115, PQ116, PQ117, PQ118, PQ119, PQ120, PQ121,
    PQ122, PQ123, PQ124, PQ125, PQ126, PQ127, PQ128, PQ129, PQ130, PQ131, PQ132,
    PQ133, PQ134, PQ135, PQ136, PQ137, PQ138, PQ139, PQ140, PQ141};

/**
 * @brief Get the buses of the 141 bus network.
 */
BusVector GetBuses() {
  // conversion from kW to MW
  for (auto& bus : buses) {
    if (bus.bus_type == BusType::kPQ) {
      bus.bus_given_values.first = bus.bus_given_values.first / 1e3;
      bus.bus_given_values.second = bus.bus_given_values.second / 1e3;
    }
  }

  // convert loads from MVA to MW and MVAr, using 0.85 power factor
  for (auto& bus : buses) {
    if (bus.bus_type == BusType::kPQ) {
      bus.bus_given_values.second =
          bus.bus_given_values.first * std::sin(std::acos(0.85));
      bus.bus_given_values.first = bus.bus_given_values.first * 0.85;
    }
  }
  return buses;
}

const std::vector<pf_solver::matpower::MatpowerBranch> branches = {
    pf_solver::matpower::MatpowerBranch(1, 2, 0.0577, 0.0409, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(2, 3, 0.1725, 0.1223, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(3, 4, 0.0009, 0.0006, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(4, 5, 0.0092, 0.0065, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(5, 6, 0.0068, 0.0049, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(6, 7, 0.0469, 0.0625, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(7, 8, 0.0736, 0.0981, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(8, 9, 0.0649, 0.0459, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(9, 10, 0.0507, 0.0359, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(10, 11, 0.0116, 0.0082, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(11, 12, 0.1291, 0.0913, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(12, 13, 0.1227, 0.0866, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(13, 14, 0.0488, 0.0345, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(14, 15, 0.0957, 0.0677, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(15, 16, 0.086, 0.0609, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(16, 17, 0.0398, 0.0282, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(17, 18, 0.0828, 0.0566, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(18, 19, 0.0186, 0.0132, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(19, 20, 0.0559, 0.0395, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(20, 21, 0.0365, 0.0246, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(21, 22, 0.0573, 0.0307, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(22, 23, 0.0263, 0.0191, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(23, 24, 0.0683, 0.0497, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(24, 25, 0.0398, 0.0282, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(25, 26, 0.0729, 0.053, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(26, 27, 0.0335, 0.0244, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(27, 28, 0.0584, 0.0414, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(28, 29, 0.0655, 0.0463, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(61, 62, 0.0411, 0.0291, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(60, 63, 0.0353, 0.025, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(63, 64, 0.1047, 0.0741, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(64, 65, 0.0674, 0.0477, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(65, 66, 0.0302, 0.0214, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(66, 67, 0.0456, 0.0323, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(67, 68, 0.0218, 0.0154, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(70, 72, 0.07, 0.0495, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(42, 73, 0.0231, 0.0164, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(73, 74, 0.003, 0.0064, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(43, 75, 0.0379, 0.0268, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(44, 76, 0.0552, 0.0391, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(46, 77, 0.0516, 0.0436, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(76, 78, 0.0167, 0.011, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(78, 79, 0.0415, 0.0101, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(79, 80, 0.1003, 0.0244, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(79, 81, 0.1513, 0.037, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(81, 82, 0.0033, 0.0008, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(47, 83, 0.0085, 0.0062, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(49, 84, 0.0517, 0.0449, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(50, 85, 0.0147, 0.0036, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(85, 86, 0.0037, 0.0016, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(86, 87, 0, 0.00001, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(7, 88, 0.0174, 0.0231, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(88, 89, 0.0469, 0.0625, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(89, 90, 0.0299, 0.0398, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(90, 91, 0.0212, 0.0283, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(91, 92, 0.0315, 0.042, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(92, 93, 0.028, 0.0373, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(93, 94, 0.0206, 0.0274, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(94, 95, 0.0206, 0.0274, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(89, 96, 0.0687, 0.0486, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(96, 97, 0.097, 0.0686, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(97, 98, 0.0902, 0.0196, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(97, 99, 0.0033, 0.0008, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(131, 132, 0.0347, 0.0245, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(131, 133, 0.092, 0.0669, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(121, 134, 0.0841, 0.0612, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(16, 135, 0.0527, 0.0373, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(16, 136, 0.0302, 0.0214, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(18, 137, 0.0584, 0.0414, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(23, 138, 0.0769, 0.0559, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(29, 30, 0.0342, 0.0248, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(30, 31, 0.0128, 0.0091, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(31, 32, 0.0347, 0.0245, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(2, 33, 0.0443, 0.0314, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(33, 34, 0.002, 0.0009, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(5, 35, 0.2274, 0.0554, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(5, 36, 0.1265, 0.1565, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(6, 37, 0.0055, 0.0073, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(37, 38, 0.2036, 0.144, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(38, 39, 0.0938, 0.0663, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(39, 40, 0.0347, 0.0245, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(40, 41, 0.0918, 0.065, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(41, 42, 0.2318, 0.164, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(42, 43, 0.1207, 0.0854, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(43, 44, 0.0443, 0.0314, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(44, 45, 0.0405, 0.0288, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(45, 46, 0.016, 0.0127, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(46, 47, 0.0636, 0.045, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(47, 48, 0.0417, 0.0295, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(48, 49, 0.0732, 0.051, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(49, 50, 0.0828, 0.0556, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(50, 51, 0.0398, 0.0282, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(51, 52, 0.0225, 0.0159, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(38, 53, 0.0841, 0.0595, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(42, 54, 0.0161, 0.0114, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(54, 55, 0.0527, 0.0373, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(55, 56, 0.0893, 0.0632, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(56, 57, 0.0867, 0.0613, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(57, 58, 0.0674, 0.0477, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(58, 59, 0.0469, 0.0332, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(55, 60, 0.0334, 0.0236, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(60, 61, 0.0327, 0.0232, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(63, 69, 0.0366, 0.0259, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(55, 70, 0.0231, 0.0164, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(70, 71, 0.012, 0.0029, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(99, 100, 0.0033, 0.0008, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(91, 101, 0.0231, 0.0164, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(101, 102, 0.0578, 0.0409, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(102, 103, 0.0889, 0.0217, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(103, 104, 0.0629, 0.0153, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(104, 105, 0.117, 0.0285, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(104, 106, 0.0114, 0.0026, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(92, 107, 0.0849, 0.0207, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(94, 108, 0.0612, 0.026, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(108, 109, 0.0452, 0.0192, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(94, 110, 0.0033, 0.0008, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(7, 111, 0.0719, 0.0509, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(10, 112, 0.107, 0.0261, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(11, 113, 0.0347, 0.0245, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(13, 114, 0.0623, 0.0441, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(114, 115, 0.0668, 0.0473, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(115, 116, 0.004, 0.001, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(14, 117, 0.0506, 0.0366, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(15, 118, 0.0161, 0.0114, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(118, 119, 0.0462, 0.0327, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(119, 120, 0.0424, 0.03, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(120, 121, 0.0507, 0.0359, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(121, 122, 0.0732, 0.0518, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(122, 123, 0.0584, 0.0414, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(123, 124, 0.061, 0.0432, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(124, 125, 0.0783, 0.0554, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(125, 126, 0.0834, 0.0607, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(126, 127, 0.0347, 0.0245, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(127, 128, 0.057, 0.042, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(128, 129, 0.0585, 0.0425, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(129, 130, 0.0103, 0.0073, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(119, 131, 0.0355, 0.0253, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(25, 139, 0.095, 0.0673, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(30, 140, 0.0519, 0.0377, 0, 0, base_z),
    pf_solver::matpower::MatpowerBranch(31, 141, 0.0584, 0.0414, 0, 0, base_z),
};

/**
 * @brief Get the admittance matrix of the 141 bus network.
 */
AdmittanceMatrix GetAdmittanceMatrix() {
  Complex2D admittance_matrix_matpower(141, Complex1D(141, {0.0, 0.0}));
  pf_solver::matpower::BuildAdmittanceMatrix(branches,
                                             admittance_matrix_matpower);
  return admittance_matrix_matpower;
}
}  // namespace matpower_case141
}  // namespace cases
}  // namespace pf_solver

#endif  // CASES_MATPOWER_CASE141_H_