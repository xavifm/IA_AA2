#pragma once
#include <vector>
#include "Vector2D.h"

class Node
{
	Vector2D position;
	float weight;
	std::vector<Node*> neighbours;

public:
	Node() : position(NULL), weight(0) {};
	Node(Vector2D position);
	Node(Vector2D position, float weight);

	Vector2D* GetPosition() { return &position; }
	float* GetWeight() { return &weight; }

	void SetNeighbour(Node* _n) { neighbours.push_back(_n); }

	std::vector<Node*>* GetNeighbours() { return &neighbours; }

	inline bool operator==(const Node& n) const { return (position.x == n.position.x) && (position.y == n.position.y); }
	inline bool operator!=(const Node& n) const { return (position.x != n.position.x) || (position.y != n.position.y); }
	inline bool operator>=(const Node& n) const { return (weight >= n.weight); }
	inline bool operator>(const Node& n) const { return (weight > n.weight); }
	inline bool operator<=(const Node& n) const { return (weight <= n.weight); }
	inline bool operator<(const Node& n) const { return (weight < n.weight); }
};