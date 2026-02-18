#pragma once
#include <vector>

struct EngineSimulationConfig {
	double ambientTemp{ 0.0 };
	double inertia{ 0.0 };
	double overheatTemp{ 0.0 };
	double hm{ 0.0 };
	double hv{ 0.0 };
	double c{ 0.0 };
	std::vector<std::pair<double, double>> torqueMap;
};