#include "FSMState_Wander.h"
#include "FSMState_Chase.h"

FSMState_Wander::FSMState_Wander()
{
	timeToChange = false;
}

void FSMState_Wander::Enter()
{

}

FSMState* FSMState_Wander::Update(Agent* agent, float dTime)
{
	bool enemySpotted = false;

	//Agent deploy state actions/movement
	
	//Transitions between states are checked here!
	if (enemySpotted) timeToChange = true;

	if (timeToChange) return new FSMState_Chase();	//Només podem passar a Chase des d'aquest estat
	else return nullptr;
}

void FSMState_Wander::Exit()
{

}
