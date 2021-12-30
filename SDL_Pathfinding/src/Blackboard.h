#pragma once
#include "Graph.h"

#include <queue>
#include <stack>
#include <unordered_map>

class Blackboard
{
	std::unordered_map<std::string, void*> theBlackboard;
	Graph* graph;

public:
	Blackboard();
	Blackboard(Grid* grid);

	void SetFloat(std::string key, float value);
	float GetFloat(std::string key);
	void SetInt(std::string key, int value);
	int GetInt(std::string key);
	void SetVector2D(std::string key, Vector2D value);
	Vector2D GetVector2D(std::string key);
	void SetGraphPtr(Graph* value);
	Graph* GetGraphPtr();
};

