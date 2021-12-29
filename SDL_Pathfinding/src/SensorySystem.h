#pragma once
#include "Vector2D.h"
#include <queue>
#include <stack>
#include "Scene.h"

/*Comprovaci� de dist�ncia de visi� (View distance).
� Comprovaci� del con de visi� (View cone).
� Comprovaci� punt de vista (Line of sight).*/

class SensorySystem
{
	Scene* world;
public:
	SensorySystem();
	SensorySystem(Scene* _world);
	float ViewDistance(Vector2D otherPos, Vector2D agentPos);
	bool CheckIfAPositionIsInsideViewCone(Vector2D otherPos, Vector2D agentPos, Vector2D agentVelocity);
	bool CheckLineOfSight(Vector2D agent1Point0, Vector2D agent1Point1, Vector2D agent2Point0, Vector2D agent2Point1);
	//void Update(Agent* agent, float dtime);
};
