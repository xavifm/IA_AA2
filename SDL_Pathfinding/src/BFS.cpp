#include "BFS.h"
#include <iostream>

std::stack<Node*> BFS::calculatePath(Vector2D* position, Vector2D* goal, Graph* graph)
{
	std::queue<Node*> frontier;
	Node* firstNode = new Node(*position);

	frontier.push(firstNode);
	std::vector<std::vector<Connection*>> came_from(graph->GetGridSize().y);

	for (int i = 0; i < graph->GetGridSize().y; i++)
	{
		std::vector<Connection*> temp(graph->GetGridSize().x);
		came_from[i] = temp;
	}

	came_from[position->y][position->x] = new Connection(firstNode, nullptr, 0);					//Weight
	Node* current;
	int count = 0;

	while (!frontier.empty())
	{
		current = frontier.front();
		frontier.pop();
		if (current->GetPosition() == *goal)
			break;
		count++;

		std::vector<Connection*> neighbours = graph->GetConnections(current);

		for (size_t i = 0; i < neighbours.size(); i++)
		{
			Node* neighbour = nullptr;
			if (neighbours[i]->GetNodeFrom()->GetPosition() == current->GetPosition())
			{
				neighbour = neighbours[i]->GetNodeTo();
			}
			else if (neighbours[i]->GetNodeTo()->GetPosition() == current->GetPosition())
			{
				neighbour = neighbours[i]->GetNodeFrom();
			}

			if (neighbours[i]->weight < 50)
			{
				if (came_from[neighbour->GetPosition().y][neighbour->GetPosition().x] == nullptr)
				{
					frontier.push(neighbour);

					came_from[neighbour->GetPosition().y][neighbour->GetPosition().x] = new Connection(current, neighbour, neighbours[i]->weight);
				}
			}
		}
	}

	std::cout << count << std::endl;

	Vector2D currentPos = *goal;
	std::stack<Node*> path;
	path.push(current);
	while (currentPos != *position)
	{
		Node* node = came_from[currentPos.y][currentPos.x]->GetNodeFrom();
		path.push(node);
		currentPos = came_from[currentPos.y][currentPos.x]->GetNodeFrom()->GetPosition();
	}
	return path;
}