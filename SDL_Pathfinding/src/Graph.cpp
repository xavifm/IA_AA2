#include "Graph.h"
#include <stack>

Connection::Connection(Node* _nodeFrom, Node* _nodeTo, float _weight)
{
	nodeFrom = _nodeFrom;
	nodeTo = _nodeTo;
	weight = _weight;

}

bool const Connection::operator==(const Vector2D& npos) const
{
	return (this->nodeFrom->GetPosition() == npos) || (this->nodeTo->GetPosition() == npos);
}

bool Node::ComparePosition(Vector2D pos)
{
	return (position == pos);
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

		Vector2D nextPos = Vector2D(currentPos.x + 1, currentPos.y);
		//Right neighbour
		if (nextPos.x < grid->getNumCellX())
		{
			if (!FindConnection(currentPos, nextPos))
			{
				Node* n = new Node(nextPos);

				stack.push(n);
				float _weight = 1 + 100 * !(grid->isValidCell(nextPos));

				connections.push_back(new Connection(current, n, _weight));
			}
		}

		nextPos = Vector2D(currentPos.x + 1, currentPos.y + 1);
		//Right down neighbour
		if (nextPos.x < grid->getNumCellX() && nextPos.y < grid->getNumCellY())
		{
			if (!FindConnection(currentPos, nextPos))
			{
				Node* n = new Node(nextPos);

				stack.push(n);
				float _weight = 1 + 100 * !(grid->isValidCell(nextPos));

				connections.push_back(new Connection(current, n, _weight));
			}
		}

		nextPos = Vector2D(currentPos.x, currentPos.y + 1);
		//Down neighbour
		if (nextPos.y < grid->getNumCellY())
		{
			if (!FindConnection(currentPos, nextPos))
			{
				Node* n = new Node(nextPos);

				stack.push(n);
				float _weight = 1 + 100 * !(grid->isValidCell(nextPos));

				connections.push_back(new Connection(current, n, _weight));
			}
		}

		nextPos = Vector2D(currentPos.x - 1, currentPos.y + 1);
		//Right down neighbour
		if (nextPos.x > 0 && nextPos.y < grid->getNumCellY())
		{
			if (!FindConnection(currentPos, nextPos))
			{
				Node* n = new Node(nextPos);

				stack.push(n);
				float _weight = 1 + 100 * !(grid->isValidCell(nextPos));

				connections.push_back(new Connection(current, n, _weight));
			}
		}
	}
}

std::vector<Connection*> Graph::GetNeighbours(Vector2D current)
{
	std::vector<Connection*> tmp;

	for each (Connection* var in connections)
	{
		if (var->GetNodeFrom()->GetPosition() == current || var->GetNodeTo()->GetPosition() == current)
		{
			tmp.push_back(var);
		}

		if (tmp.size() >= 8)
			return tmp;
	}

	return tmp;
}

bool Graph::FindConnection(Vector2D current, Vector2D next)
{
	for each (Connection * var in connections)
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
