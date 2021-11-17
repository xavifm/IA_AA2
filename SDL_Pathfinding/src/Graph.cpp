#include "Graph.h"

using namespace std;

float Connection::GetCost()
{
	return 0.0f;
}

Node* Connection::GetFromNode()
{
	return nullptr;
}

Node* Connection::GetToNode()
{
	return nullptr;
}

std::vector<Node*> Graph::GetNeighbours(Node* fromNode)
{
	return fromNode->neighbours;
}
