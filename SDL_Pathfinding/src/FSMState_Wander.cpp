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

	bool recalculateTMP = agent->GetBlackboard()->GetInt("recalculatePath");

	if (recalculateTMP)
	{
		agent->SetRandomTarget();
		agent->CalculatePath();
		agent->GetBlackboard()->SetInt("recalculatePath", 0);
	}

	if(Vector2D::Distance(agent->getPosition(), agent->getTarget()) <= 20)
	{
		agent->SetRandomTarget();
		Vector2D TMP = agent->getTarget();
		agent->CalculatePath();
	}

	bool chaseTMP = agent->GetBlackboard()->GetInt("chase");

	//Transitions between states are checked here!
	if (chaseTMP)
		timeToChange = true;

	if (timeToChange)
		return new FSMState_Chase();	//Només podem passar a Chase des d'aquest estat
	else return nullptr;
}

void FSMState_Wander::Exit()
{

}
