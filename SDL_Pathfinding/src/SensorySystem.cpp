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
	return Vector2DUtils::IsInsideCone(otherPos, agentPos, agentVelocity.Normalize() * 10, 20);
}

bool SensorySystem::CheckLineOfSight(Vector2D agent1Point0, Vector2D agent1Point1, Vector2D agent2Point0, Vector2D agent2Point1)
{
	return Vector2DUtils::SegmentSegmentIntersection(agent1Point0, agent1Point1, agent2Point0, agent2Point1);
}

void SensorySystem::Update(Agent* agent, float dtime)
{
	std::vector<Agent*> agents = *world->GetAgents();
	for (int i = 0; i < agents.size(); i++)
	{
		if (agents[i] == agent) continue;
		if(ViewDistance(agents[i]->getPosition(), agent->getPosition()) < 50 && 
			CheckIfAPositionIsInsideViewCone(agents[i]->getPosition(), agent->getPosition(), agent->getVelocity()) /* &&
			CheckLineOfSight() */)
		{
			agent->GetBlackboard()->SetVector2D("enemy" + std::to_string(i), agents[i]->getPosition());
		}
	}
	
}

std::stack<Node*> SensorySystem::CalculatePath(Vector2D target)
{
	return world->calculateNewPath(target);
}
