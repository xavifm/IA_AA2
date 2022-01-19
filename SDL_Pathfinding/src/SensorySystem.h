#pragma once
#include "Vector2D.h"
#include <queue>
#include <stack>
#include "Scene.h"
#include "Agent.h"
#include "Graph.h"
#include "Grid.h"

/*Comprovaci� de dist�ncia de visi� (View distance).
� Comprovaci� del con de visi� (View cone).
� Comprovaci� punt de vista (Line of sight).*/

class Node;
class Grid;

class SensorySystem
{
	float visionRange = CELL_SIZE * 5;
	Scene* world;
public:
	SensorySystem();
	SensorySystem(Scene* _world);
	float ViewDistance(Vector2D otherPos, Vector2D agentPos);
	bool CheckIfAPositionIsInsideViewCone(Vector2D otherPos, Vector2D agentPos, Vector2D agentVelocity);
	bool CheckLineOfSight(Vector2D agentPos, Vector2D otherPos, Grid* grid);
	void Update(Agent* agent, float dtime);
	void CalculatePath(Agent* agent);
	Vector2D GetRandomCell();
	Grid* GetGrid() { return world->GetGrid(); }
};
