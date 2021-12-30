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
	std::vector<std::vector<std::pair<Node,float>>> came_from(graph->GetGridSize().y);

	for (int i = 0; i < graph->GetGridSize().y; i++)
	{
		std::vector<std::pair<Node, float>> temp(graph->GetGridSize().x);
		came_from[i] = temp;
	}

	came_from[position->y][position->x].first = Node();				//Node
	came_from[position->y][position->x].second = 0;					//Weight
	Node* current;
	int count = 0;

	while (!frontier.empty())
	{
		current = frontier.top();
		float new_cost = came_from[current->GetPosition().y][current->GetPosition().x].second + 1;
		frontier.pop();
		if (current->GetPosition() == *goal)
			break;

		count++;

		std::vector<Connection*> neighbours = graph->GetNeighbours(current->GetPosition());

		for (size_t i = 0; i < neighbours.size(); i++)
		{
			Vector2D neighbour;
			if (neighbours[i]->GetNodeFrom()->GetPosition() == current->GetPosition())
			{
				neighbour = neighbours[i]->GetNodeTo()->GetPosition();
			}
			else if (neighbours[i]->GetNodeTo()->GetPosition() == current->GetPosition())
			{
				neighbour = neighbours[i]->GetNodeFrom()->GetPosition();
			}

			if (neighbours[i]->weight < 50)
			{
				float hCost = new_cost + Heuristic(goal, &neighbour);
				if ((came_from[neighbour.y][neighbour.x].first.GetPosition() == NULL || hCost < came_from[neighbour.y][neighbour.x].second))
				{
					Node* node = new Node(neighbour);
					frontier.push(node);

					came_from[neighbour.y][neighbour.x].first = *current;
					came_from[neighbour.y][neighbour.x].second = hCost;
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
		Node* node = new Node(came_from[currentPos.y][currentPos.x].first.GetPosition());
		path.push(node);
		currentPos = came_from[currentPos.y][currentPos.x].first.GetPosition();
	}
	return path;
}
