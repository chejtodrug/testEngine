#pragma once
#include "../Engine/IEngine.hpp"
#include "../../EngineSimulationConfig.h"

class VortecV6 : public IEngine {
private:
	EngineState state_;
	EngineSimulationConfig simulationConfig_;

public:
	explicit VortecV6(const EngineSimulationConfig& cfg);

	void Reset() override;
	void Step(double stepSec) override;

	const EngineState& GetState() const override;
	bool IsOverHeated() const override;
	double CalcTorque(double crankShaftSpeedRadSec) const;
};