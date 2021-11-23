#pragma once
#include "Vector2D.h"
#include <vector>

class Node
{
	std::vector<Vector2D> neighbours;

	void CalculateNeighbours();
public:
	Vector2D position;
	float weight;
	float cost_so_far;

	Node() : position(NULL), weight(0) {};
	Node(Vector2D position);
	Node(Vector2D position, float weight);

	int GetNeighbourCount() { return neighbours.size(); }
	Vector2D GetNeighbour(int i) { return neighbours[i]; }

	inline bool operator==(const Node& n) const { return (position.x == n.position.x) && (position.y == n.position.y); }
	inline bool operator!=(const Node& n) const { return (position.x != n.position.x) || (position.y != n.position.y); }
	inline bool operator>=(const Node& n) const { return (weight >= n.weight); }
	inline bool operator>(const Node& n) const { return (weight > n.weight); }
	inline bool operator<=(const Node& n) const { return (weight <= n.weight); }
	inline bool operator<(const Node& n) const { return (weight < n.weight); }
};