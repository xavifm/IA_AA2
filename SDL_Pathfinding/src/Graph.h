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
	inline bool operator>=(const Node& n) const { return (weight >= n.weight); }
	inline bool operator>(const Node& n) const { return (weight > n.weight); }
	inline bool operator<=(const Node& n) const { return (weight <= n.weight); }
	inline bool operator<(const Node& n) const { return (weight < n.weight); }
};