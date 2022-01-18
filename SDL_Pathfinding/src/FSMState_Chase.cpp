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
	bool looseEnemy = false;
	bool enemyHasGun = false;
	
	//Agent deploy state actions/movement
	Vector2D enemyPos = Vector2D(agent->GetBlackboard()->GetInt("enemyX"), agent->GetBlackboard()->GetInt("enemyY"));
	agent->setTarget(enemyPos);
	agent->CalculatePath();


	//Transitions between states are checked here!
	newState = new FSMState_Wander();
	if (enemyHasGun) newState = new FSMState_Flee();

	return newState;	//Els següents estats poden ser Wander o Flee
}

void FSMState_Chase::Exit()
{

}
