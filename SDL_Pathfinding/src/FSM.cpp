#include "FSM.h"
#include "FSMState_Wander.h"
#include "FSMState_Chase.h"
#include "FSMState_Flee.h"

void FSM::ChangeState(FSMState* newState)
{
	currentState->Exit();
	delete currentState;
	currentState = newState;
	currentState->Enter();
}

FSM::FSM()
{
	currentState = new FSMState_Wander();
}

FSM::~FSM()
{
	delete currentState;
}

void FSM::Update(Agent* agent, float dTime)
{
	FSMState* newState = currentState->Update(agent, dTime);
	if (newState != nullptr) ChangeState(newState);
}
