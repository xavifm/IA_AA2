#include "FSMState_Chase.h"
#include "FSMState_Wander.h"
#include "FSMState_Flee.h"

FSMState_Chase::FSMState_Chase()
{

}

void FSMState_Chase::Enter()
{

}

FSMState* FSMState_Chase::Update(Agent* agent, float dTime)
{	
	FSMState* newState = nullptr;
	bool hasEnemy = false;
	bool enemyHasGun = false;
	
	//Agent deploy state actions/movement
	Vector2D enemyPos = agent->GetBlackboard()->GetVector2D("enemy");
	agent->setTarget(enemyPos);
	agent->CalculatePath();

	enemyHasGun = bool(agent->GetBlackboard()->GetInt("flee"));
	hasEnemy = bool(agent->GetBlackboard()->GetInt("chase"));

	//Transitions between states are checked here!
	if (!hasEnemy)
		newState = new FSMState_Wander();
	else if (enemyHasGun)
		newState = new FSMState_Flee();

	return newState;	//Els següents estats poden ser Wander o Flee
}

void FSMState_Chase::Exit()
{

}
