#include "Graph.h"
#include <algorithm>

Graph::Graph(Grid* _maze)
{
	//Inicialize graph
	mapSize = Vector2D(_maze->getNumCellX(), _maze->getNumCellY());
	for (size_t i = 0; i < mapSize.x; i++)
	{
		for (size_t j = 0; j < mapSize.y; j++)
		{
			Vector2D current = Vector2D(i, j);
			float weight = 1 + (!_maze->isValidCell(current) * 100);
			graph.push_back(Node(current, weight));
		}
	}

	//Calculate neighbours
	for (size_t i = 0; i < graph.size(); i++)
	{
		Vector2D _pos = *graph[i].GetPosition();

		Node* n = GetNode(Vector2D(_pos.x - 1, _pos.y));
		if (n != nullptr)
		{
			graph[i].SetNeighbour(n);
		}
		n = GetNode(Vector2D(_pos.x + 1, _pos.y));
		if (n != nullptr)
		{
			graph[i].SetNeighbour(n);
		}
		n = GetNode(Vector2D(_pos.x, _pos.y - 1));
		if (n != nullptr)
		{
			graph[i].SetNeighbour(n);
		}
		n = GetNode(Vector2D(_pos.x, _pos.y + 1));
		if (n != nullptr)
		{
			graph[i].SetNeighbour(n);
		}
	}
}

Node* Graph::GetNode(Vector2D _pos)
{
	std::vector<Node>::iterator it = std::find(graph.begin(), graph.end(), _pos);

	if (it != graph.end())
	{
		return &(*it);
	}

	return nullptr;
}

std::vector<Node*>* Graph::GetNeighbours(Node* _node)
{
	return _node->GetNeighbours();
}