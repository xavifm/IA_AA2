#pragma once
#include "PathfindingAlgorythm.h"
#include "Graph.h"
#include "Vector2D.h"
#include <queue>
#include <stack>


class BFS : public PathfindingAlgorythm
{
	public:
		std::stack<Node*> calculatePath(Vector2D* position, Vector2D* goal, Graph* graph);
};
