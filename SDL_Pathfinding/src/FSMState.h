#pragma once
#include "Agent.h"

class FSMState
{
public:
	FSMState() = default;
	virtual ~FSMState() {};

	virtual void Enter() = 0;
	virtual FSMState* Update(Agent* agent, float dTime) = 0;
	virtual void Exit() = 0;

};

