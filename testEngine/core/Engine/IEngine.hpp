#pragma once
#include "../States/EngineState.h"

class IEngine {
public:
	virtual ~IEngine() = default;

	virtual void Reset() = 0;
	virtual void Step(double stepSec) = 0;

	virtual const EngineState& GetState() const = 0;
	virtual bool IsOverHeated() const = 0;
};