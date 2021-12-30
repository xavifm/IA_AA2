#include "Graph.h"

inline bool Connection::operator==(const Vector2D& npos) const
{
	return nodeFrom->ComparePosition(npos) || nodeTo->ComparePosition(npos);
}

bool Node::ComparePosition(Vector2D pos)
{
	return (position.x == pos.x) && (position.y == pos.y);
}

Graph::Graph(Grid* grid)
{
}
