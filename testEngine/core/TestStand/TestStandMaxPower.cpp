#include "TestStandMaxPower.h"

void TestStandMaxPower::Run(IEngine& engine, double stepSec) {

	const double epsSpeed = 1e-6;

	engine.Reset();

	auto engineState = engine.GetState();
	result_.maxPowerKW = engineState.powerKW;
	result_.speedAtMaxPowerRadSec = engineState.crankShaftSpeedRadSec;

	while (true) {
		const double prevSpeed = engineState.crankShaftSpeedRadSec;
		engine.Step(stepSec);
		engineState = engine.GetState();
		
		if (engineState.powerKW > result_.maxPowerKW) {
			result_.maxPowerKW = engineState.powerKW;
			result_.speedAtMaxPowerRadSec = engineState.crankShaftSpeedRadSec;
		}

		const double speedDelta = engineState.crankShaftSpeedRadSec - prevSpeed;
		if (speedDelta < epsSpeed) {
			break;
		}
	}
}


const MaxPowerTestResult& TestStandMaxPower::GetResult() const {
	return result_;
}
