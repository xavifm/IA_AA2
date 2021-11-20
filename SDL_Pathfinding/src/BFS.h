#pragma once
#include "PathfindingAlgorythm.h"
#include "Graph.h"
#include <queue>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include "Grid.h"
#include <filesystem>
#include <stack>
#include <map>
#include <unordered_map>
#include "Vector2D.h"


class BFS : public PathfindingAlgorythm
{
	public:
		std::stack<Node*> calculatePath(Vector2D position, Vector2D goal, Grid* graph);
};
