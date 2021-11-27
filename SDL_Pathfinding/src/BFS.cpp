#include "BFS.h"
#include <iostream>

std::stack<Node*> BFS::calculatePath(Vector2D* position, Vector2D* goal, Graph* graph)
{
	Vector2D size = *graph->GetGraphSize();

	std::queue<Node*> frontier;
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
		current = frontier.front();
		frontier.pop();
		if (*current->GetPosition() == *goal)
			break;
		count++;

		std::vector<Node*> neighbours = *graph->GetNeighbours(graph->GetNode(*current->GetPosition()));
		for (size_t i = 0; i < neighbours.size(); i++)
		{
			Node* neighbour = neighbours[i];
			if (*neighbour->GetWeight() < 100)
			{
				Vector2D neighbourPos = *neighbour->GetPosition();
				if (*came_from[neighbourPos.y][neighbourPos.x].GetPosition() == NULL)
				{
					frontier.push(new Node(neighbourPos));

					came_from[neighbourPos.y][neighbourPos.x] = *current;
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