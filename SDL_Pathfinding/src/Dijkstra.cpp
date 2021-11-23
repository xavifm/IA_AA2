#include "Dijkstra.h"

std::stack<Node*> Dijkstra::calculatePath(Vector2D* position, Vector2D* goal, Grid* graph)
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

	while (!frontier.empty())
	{
		current = frontier.top();
		float new_cost = came_from[current->position.y][current->position.x].weight + 1;
		frontier.pop();
		if (current->position == *goal)
			break;

		for (size_t i = 0; i < 4; i++)
		{
			Vector2D neighbour = current->GetNeighbour(i);

			if (graph->isValidCell(neighbour))
			{
				if (came_from[neighbour.y][neighbour.x].weight == NULL || new_cost < came_from[neighbour.y][neighbour.x].weight)
				{
					came_from[neighbour.y][neighbour.x].weight = new_cost;

					Node* node = new Node(neighbour, new_cost);
					frontier.push(node);

					came_from[neighbour.y][neighbour.x].position = current->position;
				}
			}
		}

		delete current;

		/*if (graph->isValidCell(Vector2D(current->position.x, current->position.y + 1)))
		{
			if (came_from[current->position.y + 1][current->position.x].weight == NULL || new_cost < came_from[current->position.y + 1][current->position.x].weight)
			{
				came_from[current->position.y + 1][current->position.x].weight = new_cost;
				Node* node = new Node();
				node->position = Vector2D(current->position.x, current->position.y + 1);
				node->weight = new_cost;
				frontier.push(node);
				came_from[current->position.y + 1][current->position.x].position = current->position;
			}
		}
		if (graph->isValidCell(Vector2D(current->position.x - 1, current->position.y)))
		{
			if (came_from[current->position.y][current->position.x - 1].weight == NULL || new_cost < came_from[current->position.y][current->position.x - 1].weight)
			{
				came_from[current->position.y][current->position.x - 1].weight = new_cost;
				Node* node = new Node();
				node->position = Vector2D(current->position.x - 1, current->position.y);
				node->weight = new_cost;
				frontier.push(node);
				came_from[current->position.y][current->position.x - 1].position = current->position;
			}
		}
		if (graph->isValidCell(Vector2D(current->position.x, current->position.y - 1)))
		{
			if (came_from[current->position.y - 1][current->position.x].weight == NULL || new_cost < came_from[current->position.y - 1][current->position.x].weight)
			{
				came_from[current->position.y - 1][current->position.x].weight = new_cost;
				Node* node = new Node();
				node->position = Vector2D(current->position.x, current->position.y - 1);
				node->weight = new_cost;
				frontier.push(node);
				came_from[current->position.y - 1][current->position.x].position = current->position;
			}
		}
		if (graph->isValidCell(Vector2D(current->position.x + 1, current->position.y)))
		{
			if (came_from[current->position.y][current->position.x + 1].weight == NULL || new_cost < came_from[current->position.y][current->position.x + 1].weight)
			{
				came_from[current->position.y][current->position.x + 1].weight = new_cost;
				Node* node = new Node();
				node->position = Vector2D(current->position.x + 1, current->position.y);
				node->weight = new_cost;
				frontier.push(node);
				came_from[current->position.y][current->position.x + 1].position = current->position;
			}
		}*/
	}

	Vector2D currentPos = *goal;
	std::stack<Node*> path;
	path.push(current);
	while (currentPos != *position)
	{
		path.push(new Node(currentPos));
		currentPos = came_from[currentPos.y][currentPos.x].position;
	}
	return path;
}