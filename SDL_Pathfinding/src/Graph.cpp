#include "Graph.h"
#include <stack>
#include <queue>
#include <utility>

Connection::Connection(Node* _nodeFrom, Node* _nodeTo, float _weight)
{
	nodeFrom = _nodeFrom;
	nodeTo = _nodeTo;
	weight = _weight;
	initialWeight = _weight;
}

bool const Connection::operator==(const Vector2D& npos) const
{
	return (this->nodeFrom->GetPosition() == npos) || (this->nodeTo->GetPosition() == npos);
}

Node* Connection::GetNodeNotEqual(Vector2D pos)
{
	if (nodeTo->GetPosition() == pos)
	{
		return nodeFrom;
	}
	else if (nodeFrom->GetPosition() == pos)
	{
		return nodeTo;
	}

	return nullptr;
}

void Connection::ResetWeight()
{ 
	if(weight != initialWeight)
		weight = initialWeight; 
}

bool Connection::ExistInConnection(Vector2D pos)
{
	return (nodeFrom->GetPosition() == pos) || (nodeTo->GetPosition() == pos);
}

Graph::Graph(Grid* grid)
{
	mapSize = Vector2D(grid->getNumCellX(), grid->getNumCellY());

	Vector2D initialPos = Vector2D(0, 0);
	Node* initialNode = new Node(initialPos);
	std::stack<Node*> stack;
	stack.push(initialNode);

	while (!stack.empty())
	{
		Node* current = stack.top();
		stack.pop();
		Vector2D currentPos = current->GetPosition();

		map[*current];

		Vector2D nextPos = Vector2D(currentPos.x + 1, currentPos.y);
		//Right neighbour
		if (nextPos.x < grid->getNumCellX())
		{
			if (!FindConnection(currentPos, nextPos))
			{
				Node* n = new Node(nextPos);
				map[*n];

				stack.push(n);
				float _weight = 1 + (-100 * (!grid->isValidCell(nextPos) || !grid->isValidCell(currentPos)));

				Connection* connection = new Connection(current, n, _weight);
				map[*current].push_back(connection);
				map[*n].push_back(connection);
			}
		}

		nextPos = Vector2D(currentPos.x + 1, currentPos.y + 1);
		//Right down neighbour
		if (nextPos.x < grid->getNumCellX() && nextPos.y < grid->getNumCellY())
		{
			if (!FindConnection(currentPos, nextPos))
			{
				Node* n = new Node(nextPos);
				map[*n];

				stack.push(n);
				float _weight = 1 + (-100 * (!grid->isValidCell(nextPos) || !grid->isValidCell(currentPos)));

				Connection* connection = new Connection(current, n, _weight);
				map[*current].push_back(connection);
				map[*n].push_back(connection);
			}
		}

		nextPos = Vector2D(currentPos.x, currentPos.y + 1);
		//Down neighbour
		if (nextPos.y < grid->getNumCellY())
		{
			if (!FindConnection(currentPos, nextPos))
			{
				Node* n = new Node(nextPos);
				map[*n];

				stack.push(n);
				float _weight = 1 + (-100 * (!grid->isValidCell(nextPos) || !grid->isValidCell(currentPos)));

				Connection* connection = new Connection(current, n, _weight);
				map[*current].push_back(connection);
				map[*n].push_back(connection);
			}
		}

		nextPos = Vector2D(currentPos.x - 1, currentPos.y + 1);
		//Right down neighbour
		if (nextPos.x > 0 && nextPos.y < grid->getNumCellY())
		{
			if (!FindConnection(currentPos, nextPos))
			{
				Node* n = new Node(nextPos);
				map[*n];

				stack.push(n);
				float _weight = 1 + (-100 * (!grid->isValidCell(nextPos) || !grid->isValidCell(currentPos)));
				
				Connection* connection = new Connection(current, n, _weight);
				map[*current].push_back(connection);
				map[*n].push_back(connection);
			}
		}
	}
}

Graph::~Graph()
{
	for each (Connection * var in connections)
	{
		delete var;
	}
}

bool Graph::FindConnection(Vector2D current, Vector2D next)
{
	for each (Connection * var in map[current])
	{
		if (var->GetNodeFrom()->GetPosition() == current && var->GetNodeTo()->GetPosition() == next)
		{
			return true;
		}
		else if(var->GetNodeTo()->GetPosition() == current && var->GetNodeFrom()->GetPosition() == next)
		{
			return true;
		}
	}
	return false;
}

Connection* Graph::GetConnection(Vector2D current, Vector2D next)
{
	for each (Connection * var in map[current])
	{
		if (var->GetNodeFrom()->GetPosition() == current && var->GetNodeTo()->GetPosition() == next)
		{
			return var;
		}
		else if (var->GetNodeTo()->GetPosition() == current && var->GetNodeFrom()->GetPosition() == next)
		{
			return var;
		}
	}
	return nullptr;
}

void Graph::EnemyRangeWeight(Vector2D other)
{
	std::queue<std::pair<Vector2D,Vector2D>> currentNodes;
	std::map<Node, bool> visited;
	
	currentNodes.push(std::make_pair(other, Vector2D()));
	
	while (!currentNodes.empty())
	{
		Vector2D currentNode = currentNodes.front().first;
		Vector2D prior = currentNodes.front().second;
		currentNodes.pop();
		for each (Connection * connection in map[currentNode])
		{
			if (prior == Vector2D())
			{
				if (connection->weight >= 0)
				{
					connection->ResetWeight();
					connection->weight += 1000;

					visited[currentNode] = true;
				}
				
				currentNodes.push(std::make_pair(connection->GetNodeNotEqual(currentNode)->GetPosition(), currentNode));
			}
			else if (!connection->ExistInConnection(prior) && !visited[currentNode])
			{
				if (connection->weight >= 0)
				{
					connection->ResetWeight();
					connection->weight += (GetConnection(currentNode, prior)->weight - GetConnection(currentNode, prior)->GetInitialWeight()) - 25;
					visited[currentNode] = true;
				}

				float result = connection->weight - connection->GetInitialWeight();

				if (result <= 1)
					return;
				
				currentNodes.push(std::make_pair(connection->GetNodeNotEqual(currentNode)->GetPosition(), currentNode));
			}
		}
	}
}