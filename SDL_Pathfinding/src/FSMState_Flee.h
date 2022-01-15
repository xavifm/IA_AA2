#pragma once
#include "FSMState.h"
class FSMState_Flee :
    public FSMState
{
private:

public:
	FSMState_Flee();
	~FSMState_Flee() {};

	virtual void Enter() override;
	virtual FSMState* Update(Agent* agent, float dTime) override;
	virtual void Exit() override;
};

