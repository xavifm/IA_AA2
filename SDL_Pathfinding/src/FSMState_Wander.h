#pragma once
#include "FSMState.h"

class FSMState_Wander :
    public FSMState
{
private:
	bool timeToChange;

public:
	FSMState_Wander();
	~FSMState_Wander() {};

	virtual void Enter() override;
	virtual FSMState* Update(Agent* agent, float dTime) override;
	virtual void Exit() override;
};

