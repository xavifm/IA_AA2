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

	//Transitions between states are checked here!
	if (looseEnemy) newState = new FSMState_Wander();
	if (enemyHasGun) newState = new FSMState_Flee();

	return newState;	//Els seg�ents estats poden ser Wander o Flee
}

void FSMState_Chase::Exit()
{

}
