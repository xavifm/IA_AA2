#include "A_Estrella.h"
#include <iostream>

float A_Estrella::Heuristic(Vector2D* goal, Vector2D* current)
{
	float dx = abs(goal->x - current->x);
	float dy = abs(goal->y - current->y);
	return (dx + dy);
}

std::stack<Node*> A_Estrella::calculatePath(Vector2D* position, Vector2D* goal, Grid* graph)
{
	std::priority_queue<Node*, std::vector<Node*>, std::greater_equal<Node*>> frontier;
	Node* firstNode = new Node(*position);

	frontier.push(firstNode);
	std::vector<std::vector<Node>> came_from(graph->getNumCellY());

	for (int i = 0; i < graph->getNumCellY(); i++)
	{
		std::vector<Node> temp(graph->getNumCellX());
		came_from[i] = temp;
	}

	came_from[position->y][position->x].position = NULL;
	came_from[position->y][position->x].weight = 0;
	Node* current;
	int counter = 0;
	while (!frontier.empty())
	{
		current = frontier.top();
		float new_cost = came_from[current->position.y][current->position.x].weight + 1;
		frontier.pop();
		if (current->position == *goal)
			break;
		counter++;
		for (size_t i = 0; i < 4; i++)
		{
			Vector2D neighbour = current->GetNeighbour(i);
			if (graph->isValidCell(neighbour))
			{
				float hCost = new_cost + Heuristic(goal, &neighbour);
				//Sumarli el pes del node en el graph
				if (came_from[neighbour.y][neighbour.x].weight == NULL || new_cost < came_from[neighbour.y][neighbour.x].weight)
				{
					Node* node = new Node(neighbour, hCost);
					frontier.push(node);

					came_from[neighbour.y][neighbour.x].position = current->position;
					came_from[neighbour.y][neighbour.x].weight = new_cost;
				}
			}
		}
	}

	std::cout << counter << std::endl;

	Vector2D currentPos = *goal;
	std::stack<Node*> path;
	path.push(current);
	while (currentPos != *position)
	{
		Node* node = new Node(came_from[currentPos.y][currentPos.x].position);

		path.push(node);
		currentPos = came_from[currentPos.y][currentPos.x].position;
	}
	return path;
}
