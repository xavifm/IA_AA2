#pragma once
#include "Vector2D.h"
#include <map>
#include <vector>
#include "Grid.h"
#include <iostream>
#include <functional>

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
	bool const operator<=(const Node& lhs)
	{
		return (lhs.position.x > this->GetPosition().x) || ((lhs.position.x == this->GetPosition().x) && (lhs.position.y >= this->GetPosition().y));
	}
	bool const operator>=(const Node& lhs)
	{
		return (lhs.position.x < this->GetPosition().x) || ((lhs.position.x == this->GetPosition().x) && (lhs.position.y <= this->GetPosition().y));
	}
	bool operator<(const Node& ob) const {
		return position.x < ob.position.x || (position.x == ob.position.x && position.y < ob.position.y);
	}
	bool const operator>(const Node& lhs)
	{
		return (position.x > lhs.position.x)/* || ((position.x == lhs.position.x) && (position.y > lhs.position.y)) */ ;
	}
	bool const operator<(const Node*& lhs)
	{
		return (position.x < lhs->position.x)/* || ((position.x == lhs.position.x) && (position.y < lhs.position.y))*/;
	}
	bool const operator>(const Node*& lhs)
	{
		return (position.x > lhs->position.x)/* || ((position.x == lhs.position.x) && (position.y > lhs.position.y)) */;
	}
	bool const operator!= (const Node& lhs) { return (lhs.position.x != this->GetPosition().x) || (lhs.position.y != this->GetPosition().y); }
};

struct cmpByNodePosition {
	bool operator()(const Node*& a,const Node*& b) const {
		return a < b;
	}
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
	std::map<Node, std::vector<Connection*>> map;
	std::vector<Connection*> connections;

public:
	Graph(Grid* grid);
	~Graph();

	std::vector<Connection*> GetConnections(Node* n) { return map[*n]; }

	bool FindConnection(Vector2D, Vector2D);
	Vector2D GetGridSize() { return mapSize; };
};