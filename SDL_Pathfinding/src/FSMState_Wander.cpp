#include "FSMState_Wander.h"
#include "FSMState_Chase.h"
#include "Utils.h"

FSMState_Wander::FSMState_Wander()
{
	//srand(time(NULL));
	timeToChange = false;
}

void FSMState_Wander::Enter()
{

}

FSMState* FSMState_Wander::Update(Agent* agent, float dTime)
{
	bool enemySpotted = false;
	timeToChange = false;

	//Agent deploy state actions/movement

	int recalculateTMP = agent->GetBlackboard()->GetInt("recalculatePath");

	if(recalculateTMP == 1 || Vector2D::Distance(agent->getPosition(), agent->getTarget()) <= 20)
	{
		if(recalculateTMP == 1) 
		{
			agent->SetRandomTarget();
			agent->CalculatePath();
			agent->GetBlackboard()->SetInt("recalculatePath", 0);
		}
		else 
		{
			agent->SetRandomTarget();
			Vector2D TMP = agent->getTarget();
			agent->CalculatePath();
		}
	}

	int chaseTMP = agent->GetBlackboard()->GetInt("chase");

	//Transitions between states are checked here!
	if (chaseTMP)
		timeToChange = true;

	if (timeToChange) return new FSMState_Chase();	//Nom�s podem passar a Chase des d'aquest estat
	else return nullptr;
}

void FSMState_Wander::Exit()
{

}
