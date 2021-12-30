#include "A_Estrella.h"
#include <iostream>

float A_Estrella::Heuristic(Vector2D* goal, Vector2D* current)
{
	float dx = abs(goal->x - current->x);
	float dy = abs(goal->y - current->y);
	return (dx + dy);
}

std::stack<Node*> A_Estrella::calculatePath(Vector2D* position, Vector2D* goal, Graph* graph)
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

	came_from[position->y][position->x].SetPosition(NULL);
	came_from[position->y][position->x].weight = 0;
	Node* current;
	int counter = 0;
	int frontierPos = 0;
	while (!frontier.empty())
	{
		current = frontier.top();
		float new_cost = came_from[current->GetPosition().y][current->GetPosition().x].weight + 1;
		frontier.pop();
		if (current->GetPosition() == *goal)
			break;
		counter++;
		for (size_t i = frontierPos; i < frontierPos+4; i++)
		{
			Vector2D neighbour = graph->connections[i]->GetNodeTo()->GetPosition();
			float hCost = new_cost + Heuristic(goal, &neighbour);
			//Sumarli el pes del node en el graph
			if (came_from[neighbour.y][neighbour.x].weight == NULL || new_cost < came_from[neighbour.y][neighbour.x].weight)
			{
				Node* node = new Node(neighbour);
				node->weight = hCost;
				frontier.push(node);

				came_from[neighbour.y][neighbour.x].SetPosition(current->GetPosition());
				came_from[neighbour.y][neighbour.x].weight = new_cost;
			}
			frontierPos++;
		}
	}

	std::cout << counter << std::endl;

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
