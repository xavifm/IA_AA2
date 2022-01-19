#include "FSMState_Flee.h"
#include "FSMState_Wander.h"
#include "FSMState_Chase.h"

FSMState_Flee::FSMState_Flee()
{

}

void FSMState_Flee::Enter()
{

}

FSMState* FSMState_Flee::Update(Agent* agent, float dTime)
{
	FSMState* newState = nullptr;
	bool hasEnemy = true;
	bool enemyHasGun = false;

	//Agent deploy state actions/movement
	//Modificar els booleans aqui
	Vector2D enemyPos = Vector2D(agent->GetBlackboard()->GetInt("enemyX"), agent->GetBlackboard()->GetInt("enemyY"));
	agent->setTarget(enemyPos);
	agent->CalculatePath();

	enemyHasGun = bool(agent->GetBlackboard()->GetInt("flee"));
	hasEnemy = bool(agent->GetBlackboard()->GetInt("chase"));

	//Transitions between states are checked here!
	if (!hasEnemy)
		newState = new FSMState_Wander();
	else if (!enemyHasGun)
		newState = new FSMState_Chase();

	return newState;	//Els següents estats poden ser Wander o Flee
}

void FSMState_Flee::Exit()
{

}
