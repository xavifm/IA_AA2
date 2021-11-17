#pragma once
#include "Vector2D.h"
#include <vector>

struct Node
{
	Vector2D position;
	std::vector<Node*> neighbours;
	float weight;

	inline bool operator==(const Node& n) const { return (position.x == n.position.x) && (position.y == n.position.y); }
	inline bool operator!=(const Node& n) const { return (position.x != n.position.x) || (position.y != n.position.y); }
};

class Connection 
{
	Node* from, * to;
	float cost;
public:
	float GetCost();
	Node* GetFromNode();
	Node* GetToNode();
};

class Graph
{
	std::vector<Connection> connections;
public:
	Connection* GetConnections(Node* fromNode);
	std::vector<Node*> GetNeighbours(Node* fromNode);
};
