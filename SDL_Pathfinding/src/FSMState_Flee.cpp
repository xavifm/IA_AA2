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
	bool looseEnemy = false;
	bool enemyLooseGun = false;

	//Agent deploy state actions/movement
	//Modificar els booleans aqui

	//Transitions between states are checked here!
	if (looseEnemy) newState = new FSMState_Wander();
	if (enemyLooseGun) newState = new FSMState_Chase();

	return newState;	//Els següents estats poden ser Wander o Flee
}

void FSMState_Flee::Exit()
{

}
