#pragma once
#include "ITestStand.h"

struct OverheatTestResult {
	double timeToOverheatSec{0.0};
};

class TestStandOverheat : public ITestStand {
private:
	OverheatTestResult result_{};

public:
	void Run(IEngine& engine, double stepSec) override;
	const OverheatTestResult& GetResult() const;
};