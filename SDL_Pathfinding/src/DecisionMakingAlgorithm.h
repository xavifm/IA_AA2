#pragma once
#include "Agent.h"

class DecisionMakingAlgorithm
{
public:
	DecisionMakingAlgorithm() = default;
	virtual ~DecisionMakingAlgorithm() {};

	virtual void Update(Agent* agent, float dTime) = 0;
};

