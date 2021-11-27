#include "Greedy.h"
#include <math.h>
#include <iostream>

float Greedy::Heuristic(Vector2D* goal, Vector2D* current)
{
	float dx = abs(goal->x - current->x);
	float dy = abs(goal->y - current->y);
	return (dx + dy);
}

std::stack<Node*> Greedy::calculatePath(Vector2D* position, Vector2D* goal, Graph* graph)
{
	Vector2D size = *graph->GetGraphSize();

	std::priority_queue<Node*, std::vector<Node*>, std::greater_equal<Node*>> frontier;
	Node* firstNode = new Node(*position);

	frontier.push(firstNode);
	std::vector<std::vector<Node>> came_from(size.y);

	for (int i = 0; i < size.y; i++)
	{
		std::vector<Node> temp(size.x);
		came_from[i] = temp;
	}

	came_from[position->y][position->x] = Node();
	Node* current;
	int count = 0;

	while (!frontier.empty())
	{
		current = frontier.top();
		Vector2D currentPos = *current->GetPosition();
		float new_cost = *came_from[currentPos.y][currentPos.x].GetWeight() + 1;
		frontier.pop();
		if (currentPos == *goal)
			break;
		count++;

		std::vector<Node*> neighbours = *graph->GetNeighbours(graph->GetNode(currentPos));
		for (size_t i = 0; i < neighbours.size(); i++)
		{
			Node* neighbour = neighbours[i];
			if (*neighbour->GetWeight() < 100)
			{
				float hCost = new_cost + Heuristic(goal, neighbour->GetPosition());
				Vector2D neighbourPos = *neighbour->GetPosition();
				if ((*came_from[neighbourPos.y][neighbourPos.x].GetPosition() == NULL || hCost < *came_from[neighbourPos.y][neighbourPos.x].GetWeight()))
				{
					frontier.push(new Node(neighbourPos, hCost));

					came_from[neighbourPos.y][neighbourPos.x] = Node(currentPos, hCost);
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
		path.push(new Node(*came_from[currentPos.y][currentPos.x].GetPosition()));
		currentPos = *came_from[currentPos.y][currentPos.x].GetPosition();
	}
	return path;
}
