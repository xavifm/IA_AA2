#pragma once
#include "Vector2D.h"
#include <vector>
#include "Grid.h"

class Node
{
	Vector2D position;

public:
	Node() : position(NULL) {};
	Node(Vector2D position) : position(position) {};

	Vector2D GetPosition() { return position; }
	bool ComparePosition(Vector2D pos);


	inline bool operator==(const Node& n) const { return (position.x == n.position.x) && (position.y == n.position.y); }
	inline bool operator!=(const Node& n) const { return (position.x != n.position.x) || (position.y != n.position.y); }
};

class Connection
{
	Node* nodeFrom;
	Node* nodeTo;
public:
	float weight;
	Node* GetNodeFrom() { return nodeFrom; };
	Node* GetNodeTo() { return nodeTo; };

	inline bool operator==(const Vector2D& npos) const;
};

class Graph
{
public:
	Graph(Grid* grid);
	std::vector<Connection*> connections;
};