#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <stack>
#include "Vector2D.h"

class Node;
class Agent;
class Grid;

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() {};
	virtual void update(float dtime, SDL_Event *event) = 0;
	virtual void draw() = 0;
	virtual const char* getTitle() { return ""; };

	virtual std::vector<Agent*>* GetAgents() = 0;
	virtual std::stack <Node*> calculateNewPath(Vector2D target) = 0;
	virtual Grid* GetGrid() = 0;
};

