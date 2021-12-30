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

	bool const operator==(const Node& lhs)
	{
		return (lhs.position.x == this->GetPosition().x) && (lhs.position.y == this->GetPosition().y);
	}
	bool const operator!= (const Node& lhs) { return (lhs.position.x != this->GetPosition().x) || (lhs.position.y != this->GetPosition().y); }
};

class Connection
{
	Node* nodeFrom = nullptr;
	Node* nodeTo = nullptr;
public:
	Connection(Node* _nodeFrom, Node* _nodeTo, float weight);

	float weight;
	Node* GetNodeFrom() { return nodeFrom; };
	Node* GetNodeTo() { return nodeTo; };

	bool const operator==(const Vector2D& npos) const;
};

class Graph
{
	Vector2D mapSize;

public:
	Graph(Grid* grid);
	std::vector<Connection*> connections;


	std::vector<Connection*> GetNeighbours(Vector2D);

	bool FindConnection(Vector2D, Vector2D);
	Vector2D GetGridSize() { return mapSize; };
};