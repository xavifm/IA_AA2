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
	std::priority_queue<Node*, std::vector<Node*>, std::greater_equal<Node*>> frontier;
	Node* firstNode = new Node(*position);

	frontier.push(firstNode);
	std::vector<std::vector<Node>> came_from(graph->gridSizeY);

	for (int i = 0; i < graph->gridSizeY; i++)
	{
		std::vector<Node> temp(graph->gridSizeX);
		came_from[i] = temp;
	}

	came_from[position->y][position->x].GetPosition() = NULL;
	came_from[position->y][position->x].weight = 0;
	Node* current;
	int count = 0;
	int frontierPos = 0;

	while (!frontier.empty())
	{
		current = frontier.top();
		float new_cost = came_from[current->GetPosition().y][current->GetPosition().x].weight + 1;
		frontier.pop();
		if (current->GetPosition() == *goal)
			break;
		count++;
		for (size_t i = frontierPos; i < frontierPos + 4; i++)
		{
			Vector2D neighbour = graph->connections[i]->GetNodeTo()->GetPosition();
			float hCost = new_cost + Heuristic(goal, &neighbour);
			if ((came_from[neighbour.y][neighbour.x].GetPosition() == NULL || hCost < came_from[neighbour.y][neighbour.x].weight))
			{
				Node* node = new Node(neighbour);
				node->weight = hCost;
				frontier.push(node);

				came_from[neighbour.y][neighbour.x].GetPosition() = current->GetPosition();
				came_from[neighbour.y][neighbour.x].weight = hCost;
			}
			frontierPos++;
		}
	}

	std::cout << count << std::endl;

	Vector2D currentPos = *goal;
	std::stack<Node*> path;
	path.push(current);
	while (currentPos != *position)
	{
		Node* node = new Node(came_from[currentPos.y][currentPos.x].GetPosition());
		path.push(node);
		currentPos = came_from[currentPos.y][currentPos.x].GetPosition();
	}
	return path;
}
