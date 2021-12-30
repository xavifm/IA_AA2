#include "Blackboard.h"

Blackboard::Blackboard()
{
}

void Blackboard::SetFloat(std::string key, float value)
{
	theBlackboard[key] = &value;
}

float Blackboard::GetFloat(std::string key)
{
	return *(float*)theBlackboard[key];
}

void Blackboard::SetInt(std::string key, int value)
{
	theBlackboard[key] = &value;
}

int Blackboard::GetInt(std::string key)
{
	return *(int*)theBlackboard[key];
}

/*void Blackboard::SetVector2D(std::string key, Vector2D value)
{
	theBlackboard[key] = &value;
}

Vector2D Blackboard::GetVector2D(std::string key)
{
	return *(Vector2D*)theBlackboard[key];
}

void Blackboard::SetGraphPtr(Graph* value)
{
	//graph = value;
}

Graph* Blackboard::GetGraphPtr()
{
	//return graph;
	return nullptr;
}*/
