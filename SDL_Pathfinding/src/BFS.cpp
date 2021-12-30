#include "BFS.h"
#include <iostream>

std::stack<Node*> BFS::calculatePath(Vector2D* position, Vector2D* goal, Graph* graph)
{
	std::queue<Node*> frontier;
	Node* firstNode = new Node(*position);

	frontier.push(firstNode);
	std::vector<std::vector<Node>> came_from(graph->gridSizeY);

	for (int i = 0; i < graph->gridSizeY; i++)
	{
		std::vector<Node> temp(graph->gridSizeX);
		came_from[i] = temp;
	}

	came_from[position->y][position->x].SetPosition(NULL);
	came_from[position->y][position->x].weight = 0;
	Node* current;
	int count = 0;
	int frontierPos = 0;

	while (!frontier.empty())
	{
		current = frontier.front();
		frontier.pop();
		if (current->GetPosition() == *goal)
			break;
		count++;
		int aux = frontierPos + 4;

		for each (Connection* con in graph->connections)
		{
			if(con->GetNodeFrom()->GetPosition() == current->GetPosition())
			{
				if (con->GetNodeTo()->GetPosition() != NULL)
				{
					frontier.push(new Node(con->GetNodeTo()->GetPosition()));

					came_from[con->GetNodeTo()->GetPosition().y][con->GetNodeTo()->GetPosition().x].SetPosition(current->GetPosition());
					std::cout << came_from[con->GetNodeTo()->GetPosition().y][con->GetNodeTo()->GetPosition().x].GetPosition().x << std::endl;
				}
			}
		}

		/*for (size_t i = 0; i < graph->connections; i++)
		{
			Vector2D neighbour = current->GetNeighbour(i);
			if (graph->isValidCell(neighbour))
			{
				if (came_from[neighbour.y][neighbour.x].GetPosition() == NULL)
				{
					frontier.push(new Node(neighbour));

					came_from[neighbour.y][neighbour.x].GetPosition() = current->GetPosition();
				}
			}
		}*/
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

	std::cout << count << std::endl;

	return path;
}