#include "A_Estrella.h"
#include <iostream>

float A_Estrella::Heuristic(Vector2D* goal, Vector2D* current)
{
	float D_PARAM = 1;
	float D2_PARAM = 1;

	float dx = abs(goal->x - current->x);
	float dy = abs(goal->y - current->y);
	return D_PARAM * (dx + dy) + (D2_PARAM - 2 * D_PARAM) * min(dx, dy);
}

std::stack<Node*> A_Estrella::calculatePath(Vector2D* position, Vector2D* goal, Graph* graph)
{
	std::priority_queue<Node*, std::vector<Node*>, std::greater_equal<Node*>> frontier;
	Node* firstNode = new Node(*position);

	firstNode->priority = Heuristic(goal, position);

	frontier.push(firstNode);
	std::vector<std::vector<std::pair<Node, float>>> came_from(graph->GetGridSize().y);

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
		float new_cost = came_from[current->GetPosition().y][current->GetPosition().x].second;
		frontier.pop();
		if (current->GetPosition() == *goal)
			break;
		count++;

		std::vector<Connection*> neighbours = graph->GetConnections(current);

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

			if (neighbours[i]->GetInitialWeight() >= 0 && neighbours[i]->weight != -100)
			{
				new_cost += neighbours[i]->weight;

				float hCost = new_cost + Heuristic(goal, &neighbour);

				//Sumarli el pes del node en el graph
				if (came_from[neighbour.y][neighbour.x].second == NULL || new_cost < came_from[neighbour.y][neighbour.x].second)
				{
					Node* node = new Node(neighbour);
					node->priority = hCost;

					frontier.push(node);

					bool tmp = node < current;

					came_from[neighbour.y][neighbour.x].first = *current;
					came_from[neighbour.y][neighbour.x].second = new_cost;
				}
			}
			else if (neighbours[i]->weight == -100)
				neighbours[i]->weight = 1;
		}
	}

	std::cout << count << std::endl;

	Vector2D currentPos = *goal;
	std::stack<Node*> path;
	path.push(current);

	int functionError = 0;
	while (currentPos != *position)
	{
		/*if (functionError >= 99999)
			break;*/

		Node* node = new Node(came_from[currentPos.y][currentPos.x].first.GetPosition());

		path.push(node);
		currentPos = came_from[currentPos.y][currentPos.x].first.GetPosition();
		functionError++;

	}
	/*if(functionError < 99999)*/
	return path;
}
