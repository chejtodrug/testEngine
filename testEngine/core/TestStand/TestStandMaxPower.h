#pragma once
#include "ITestStand.h"

struct MaxPowerTestResult {
	double maxPowerKW{0.0};
	double speedAtMaxPowerRadSec{0.0};
};

class TestStandMaxPower : public ITestStand {
private:
	MaxPowerTestResult result_{};
public:
	void Run(IEngine& engine, double stepSec) override;
	const MaxPowerTestResult& GetResult() const;

};