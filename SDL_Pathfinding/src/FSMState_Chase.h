#pragma once
#include "FSMState.h"

class FSMState_Chase :
	public FSMState
{
private:

public:
	FSMState_Chase();
	~FSMState_Chase() {};

	virtual void Enter() override;
	virtual FSMState* Update(Agent* agent, float dTime) override;
	virtual void Exit() override;
};

