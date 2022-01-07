#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>

class Agent;

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() {};
	virtual void update(float dtime, SDL_Event *event) = 0;
	virtual void draw() = 0;
	virtual const char* getTitle() { return ""; };

	virtual std::vector<Agent*>* GetAgents() = 0;
};

