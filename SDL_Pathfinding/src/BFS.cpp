#include "BFS.h"

std::stack<Node*> BFS::calculatePath(Vector2D* position, Vector2D* goal, Grid* graph)
{
	std::queue<Node*> frontier;
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

	while (!frontier.empty())
	{
		current = frontier.front();
		frontier.pop();
		if (current->position == *goal)
			break;

		for (size_t i = 0; i < current->GetNeighbourCount(); i++)
		{
			Vector2D neighbour = current->GetNeighbour(i);
			if (graph->isValidCell(neighbour))
			{
				if (came_from[neighbour.y][neighbour.x].position == NULL)
				{
					frontier.push(new Node(neighbour));

					came_from[neighbour.y][neighbour.x].position = current->position;
				}
			}
		}
	}

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