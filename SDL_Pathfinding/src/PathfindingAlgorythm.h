#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Path.h"
#include "Vector2D.h"
#include "utils.h"
#include "Graph.h"


class PathfindingAlgorythm
{
	public:
		void applyPath(Node* current);
};

