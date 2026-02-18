#include "VortecV6.h"
#include <algorithm>
#include <stdexcept>

VortecV6::VortecV6(const EngineSimulationConfig& simulationConfig)
	:simulationConfig_(simulationConfig)
{
	const auto& torqueMap = simulationConfig.torqueMap;
	if (torqueMap.empty() || torqueMap.size() < 2) {
		throw std::invalid_argument("Ошибка конфигурации двигателя: torqueMap не должна быть пустой и содержать минимум 2 точки ");
	}
}

void VortecV6::Reset() {
	state_.workingTimeSec = 0.0;
	state_.crankShaftSpeedRadSec = 0.0;
	state_.temperature = simulationConfig_.ambientTemp;
	state_.torqueNM = CalcTorque(0.0);
	state_.powerKW = 0.0;
}

double VortecV6::CalcTorque(double crankShaftSpeedRadSec) const {
	const auto& torqueMap = simulationConfig_.torqueMap;
	const double speed = crankShaftSpeedRadSec;

	for (size_t i = 0; i < torqueMap.size() - 1; i++) {
		const double v1 = torqueMap[i].first;
		const double m1 = torqueMap[i].second;
		const double v2 = torqueMap[i + 1].first;
		const double m2 = torqueMap[i + 1].second;

		if (speed >= v1 && speed <= v2) {
			if (speed == v1) return m1;
			if (speed == v2) return m2;
			double torque = m1 + (speed - v1) * ((m2 - m1) / (v2 - v1));
			return torque;
		}
	}

	return torqueMap.back().second;
}

void VortecV6::Step(double stepSec) {
	const double speed = state_.crankShaftSpeedRadSec;
	const double torque = CalcTorque(speed);
	const double acceleration = torque / simulationConfig_.inertia;
	double newSpeed = speed + (acceleration * stepSec);
	if (newSpeed < 0) {
		newSpeed = 0;
	}
	const double heatingRate = (torque * simulationConfig_.hm) + ((newSpeed * newSpeed) * simulationConfig_.hv);
	const double coolingRate = simulationConfig_.c * (simulationConfig_.ambientTemp - state_.temperature);
	const double newTemperature = state_.temperature + (heatingRate + coolingRate) * stepSec;
	const double powerKW = (torque * newSpeed) / 1000.0;

	state_.workingTimeSec += stepSec;
	state_.crankShaftSpeedRadSec = newSpeed;
	state_.temperature = newTemperature;
	state_.torqueNM = torque;
	state_.powerKW = powerKW;
}


bool VortecV6::IsOverHeated() const {
	constexpr double eps = 1e-9;
	return state_.temperature >= simulationConfig_.overheatTemp - eps;
}

const EngineState& VortecV6::GetState() const {
	return state_;
}