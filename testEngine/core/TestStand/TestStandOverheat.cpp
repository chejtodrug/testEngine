#include "TestStandOverheat.h"
#include <iostream>

void TestStandOverheat::Run(IEngine& engine, double stepSec) {
	engine.Reset();

	double nextPrintTimeSec = 1.0;

	while (!engine.IsOverHeated()) {

		const auto& engineState = engine.GetState();

		engine.Step(stepSec);

		if (engineState.workingTimeSec >= nextPrintTimeSec) {
			std::cout << "TestStandOverheat: Время работы двигателя: " << engineState.workingTimeSec << " сек, Температура: " << engineState.temperature << " C\n";
	
			nextPrintTimeSec += 1.0;
		}
		
	}

	result_.timeToOverheatSec = engine.GetState().workingTimeSec;
}


const OverheatTestResult& TestStandOverheat::GetResult() const {
	return result_;
}