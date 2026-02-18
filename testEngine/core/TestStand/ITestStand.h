#pragma once
#include "../Engine/IEngine.hpp"

class ITestStand {
public:
	virtual ~ITestStand() = default;
	virtual void Run(IEngine& engine, double stepSec) = 0;
};