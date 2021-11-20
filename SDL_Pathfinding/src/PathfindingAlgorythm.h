#pragma once
#include <iostream>
#include <minmax.h>
#include "Grid.h"
#include "Graph.h"
#include <SDL.h>
#include "SDL_SimpleApp.h"
#include "Vector2D.h"
#include "utils.h"
#include <stack>


class PathfindingAlgorythm
{
	public:
		virtual std::stack<Node*> calculatePath(Vector2D* position, Vector2D* goal, Grid* graph) = 0;
};

