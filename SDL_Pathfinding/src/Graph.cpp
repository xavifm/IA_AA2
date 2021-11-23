#include "Graph.h"

void Node::CalculateNeighbours()
{
	neighbours.push_back(Vector2D(position.x + 1, position.y));
	neighbours.push_back(Vector2D(position.x - 1, position.y));
	neighbours.push_back(Vector2D(position.x, position.y + 1));
	neighbours.push_back(Vector2D(position.x, position.y - 1));
}

Node::Node(Vector2D _position)/* :position(position), weight(0)*/
{
	position = _position;
	weight = 0;
	CalculateNeighbours();
}

Node::Node(Vector2D _position, float _weight)/* : position(position), weight(weight)*/
{
	position = _position;
	weight = _weight;
	CalculateNeighbours();
}
