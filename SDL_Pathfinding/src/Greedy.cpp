#include "Greedy.h"
#include <math.h>

float Greedy::Heuristic(Vector2D* goal, Vector2D* current)
{
	float dx = abs(goal->x - current->x);
	float dy = abs(goal->y - current->y);
	return (dx + dy);
}

std::stack<Node*> Greedy::calculatePath(Vector2D* position, Vector2D* goal, Grid* graph)
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
	Node* current;

	while (!frontier.empty())
	{
		current = frontier.top();
		float new_cost = came_from[current->position.y][current->position.x].weight + 1;
		frontier.pop();
		if (current->position == *goal)
			break;

		for (size_t i = 0; i < current->GetNeighbourCount(); i++)
		{
			Vector2D neighbour = current->GetNeighbour(i);
			if (graph->isValidCell(neighbour) && (came_from[neighbour.y][neighbour.x].position == NULL || new_cost < came_from[current->position.y + 1][current->position.x].weight ||new_cost < came_from[current->position.y + 1][current->position.x].cost_so_far))
			{
				came_from[neighbour.y][neighbour.x].cost_so_far = new_cost;
				float hCost = new_cost + Heuristic(goal, &neighbour);

				Node* node = new Node(neighbour, hCost);
				node->cost_so_far = new_cost;
				frontier.push(node);

				came_from[neighbour.y][neighbour.x].position = current->position;
			}
		}

		/*if (graph->isValidCell(Vector2D(current->position.x, current->position.y + 1)) && came_from[current->position.y + 1][current->position.x].position == NULL)
		{
			float new_cost = Heuristic(goal, new Vector2D(current->position.x, current->position.y + 1));

			Node* node = new Node(Vector2D(current->position.x, current->position.y + 1), new_cost);
			frontier.push(node);

			came_from[current->position.y + 1][current->position.x].position = current->position;
		}
		if (graph->isValidCell(Vector2D(current->position.x - 1, current->position.y)) && came_from[current->position.y][current->position.x - 1].position == NULL)
		{
			float new_cost = Heuristic(goal, new Vector2D(current->position.x - 1, current->position.y));

			Node* node = new Node(Vector2D(current->position.x - 1, current->position.y), new_cost);
			frontier.push(node);

			came_from[current->position.y][current->position.x - 1].position = current->position;
		}
		if (graph->isValidCell(Vector2D(current->position.x, current->position.y - 1)) && came_from[current->position.y - 1][current->position.x].position == NULL)
		{
			float new_cost = Heuristic(goal, new Vector2D(current->position.x, current->position.y - 1));

			Node* node = new Node(Vector2D(current->position.x, current->position.y - 1), new_cost);
			frontier.push(node);

			came_from[current->position.y - 1][current->position.x].position = current->position;
		}
		if (graph->isValidCell(Vector2D(current->position.x + 1, current->position.y)) && came_from[current->position.y][current->position.x + 1].position == NULL)
		{
			float new_cost = Heuristic(goal, new Vector2D(current->position.x + 1, current->position.y));

			Node* node = new Node(Vector2D(current->position.x + 1, current->position.y), new_cost);
			frontier.push(node);

			came_from[current->position.y][current->position.x + 1].position = current->position;
		}*/
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
