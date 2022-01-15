#pragma once
#include "DecisionMakingAlgorithm.h"
#include "FSMState.h"

class FSM :
    public DecisionMakingAlgorithm
{
private:
    FSMState* currentState;

    void ChangeState(FSMState* newState);

public:
    FSM();
    ~FSM();

    virtual void Update(Agent* agent, float dTime) override;

};

