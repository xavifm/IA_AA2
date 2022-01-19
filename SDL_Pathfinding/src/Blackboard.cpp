#include "Blackboard.h"

Blackboard::Blackboard()
{
}

Blackboard::~Blackboard()
{
	delete graph;
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
	theBlackboard[key] = (int*)value;
}

int Blackboard::GetInt(std::string key)
{
	return (int) theBlackboard[key];
}

void Blackboard::SetVector2D(std::string key, Vector2D value)
{
    float* tmp = new float(value.x);
    theBlackboard[key + "x"] = tmp;

    tmp = new float(value.y);
    theBlackboard[key + "y"] = tmp;

    graph->EnemyRangeWeight(value);
}

Vector2D Blackboard::GetVector2D(std::string key)
{
    Vector2D tmp;
    tmp.x = *(float*)theBlackboard[key + "x"];
    tmp.y = *(float*)theBlackboard[key + "y"];

    return tmp;
}

void Blackboard::SetGraphPtr(Graph* value)
{
	graph = value;
}

Graph* Blackboard::GetGraphPtr()
{
	return graph;
}
