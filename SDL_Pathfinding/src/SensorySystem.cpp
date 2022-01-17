#include "SensorySystem.h"
#include <string>

SensorySystem::SensorySystem()
{
	world = nullptr;
}

SensorySystem::SensorySystem(Scene* _world)
{
	world = _world;
}

float SensorySystem::ViewDistance(Vector2D otherPos, Vector2D agentPos)
{
	return Vector2D::Distance(agentPos, otherPos);
}

bool SensorySystem::CheckIfAPositionIsInsideViewCone(Vector2D otherPos, Vector2D agentPos, Vector2D agentVelocity)
{
	return Vector2DUtils::IsInsideCone(otherPos, agentPos, agentPos + agentVelocity.Normalize() * visionRange, 20);
}

bool SensorySystem::CheckLineOfSight(Vector2D agentPos, Vector2D otherPos, Grid* grid)
{
	bool isValid = true;
	Vector2D intersectionPoint;
	Vector2D distance = grid->pix2cell(agentPos - otherPos);

	Vector2D gridSize = Vector2D(grid->getNumCellX(), grid->getNumCellY());

	Vector2D agentCellPos = grid->pix2cell(agentPos);

	for (size_t i = 1; i <= abs(distance.x); i++)
	{
		int value = i;
		if (distance.x < 0) value *= -1;
		intersectionPoint = Vector2D(-1, -1);
		Vector2DUtils::SegmentSegmentIntersection(agentPos, otherPos, grid->cell2pix(Vector2D(agentCellPos.x + value, 0)), grid->cell2pix(Vector2D(agentCellPos.x + value, gridSize.y - 1)), true, &intersectionPoint);
		if (intersectionPoint != Vector2D(-1, -1) && !grid->isValidCell(intersectionPoint))
			return false;
	}

	for (size_t i = 1; i <= abs(distance.y); i++)
	{
		int value = i;
		if (distance.y > 0) value *= -1;
		intersectionPoint = Vector2D(-1, -1);
		Vector2DUtils::SegmentSegmentIntersection(agentPos, otherPos, grid->cell2pix(Vector2D(0, agentCellPos.y + value)), grid->cell2pix(Vector2D(gridSize.x - 1, agentCellPos.y + value)), true, &intersectionPoint);
		if (intersectionPoint != Vector2D(-1, -1) && !grid->isValidCell(intersectionPoint))
			return false;
	}

	return true;
}

void SensorySystem::Update(Agent* agent, float dtime)
{
	std::vector<Agent*> agents = *world->GetAgents();
	for (int i = 0; i < agents.size(); i++)
	{
		if (agents[i] == agent) continue;
		
		if(ViewDistance(agents[i]->getPosition(), agent->getPosition()) <= visionRange && 
			CheckIfAPositionIsInsideViewCone(agents[i]->getPosition(), agent->getPosition(), agent->getVelocity()) &&
			CheckLineOfSight(agent->getPosition(), agents[i]->getPosition(), world->GetGrid()))
		{
			agent->GetBlackboard()->SetVector2D("enemy" + std::to_string(i), agents[i]->getPosition());
		}
	}
}

std::stack<Node*> SensorySystem::CalculatePath(Vector2D target)
{
	return world->calculateNewPath(target);
}
