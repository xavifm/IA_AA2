#include "SensorySystem.h"

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
	Agent* other = nullptr;
	if(world->GetAgents()->size() <= 1) 
	{
		return;
	}
	if((*world->GetAgents())[1] == agent) 
	{
		other = (*world->GetAgents())[0];
	}
	else if((*world->GetAgents())[0] == agent) 
	{
		other = (*world->GetAgents())[1];
	}
	if(other != nullptr) 
	{
		if((ViewDistance(other->getPosition(), agent->getPosition()) < 50 || CheckIfAPositionIsInsideViewCone(other->getPosition(), agent->getPosition(), agent->getVelocity()))) 
		{
			agent->GetBlackboard()->SetVector2D("enemy", other->getPosition());
		}
	}
}