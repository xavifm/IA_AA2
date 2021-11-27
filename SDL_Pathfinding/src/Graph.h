#pragma once
#include "Node.h"
#include "Grid.h"
#include "Vector2D.h"
#include <vector>

class Graph
{
	Vector2D mapSize;
	std::vector<Node> graph;

public:
	Graph() {}
	Graph(Grid*);

	Vector2D* GetGraphSize() { return &mapSize; }
	Node* GetNode(Vector2D);
	std::vector<Node*>* GetNeighbours(Node*);


};