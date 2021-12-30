#include "Graph.h"
#include <stack>

Connection::Connection(Node* _nodeFrom, Node* _nodeTo, float _weight)
{
    nodeFrom = _nodeFrom;
    nodeTo = _nodeTo;
    weight = _weight;

}

inline bool Connection::operator==(const Vector2D& npos) const
{
    return nodeFrom->ComparePosition(npos) || nodeTo->ComparePosition(npos);
}

bool Node::ComparePosition(Vector2D pos)
{
    return (position.x == pos.x) && (position.y == pos.y);
}

Graph::Graph(Grid* grid)
{
    bool** visitedNode;
    visitedNode = new bool* [grid->getNumCellY()];

    for (size_t y = 0; y < grid->getNumCellY(); y++)
    {
        visitedNode[y] = new bool[grid->getNumCellX()];

        for (size_t x = 0; x < grid->getNumCellX(); x++)
        {
            visitedNode[y][x] = false;
        }
    }

    Vector2D initialPos = Vector2D(0, 0);
    Node* initialNode = new Node(initialPos);
    std::stack<Node*> stack;
    stack.push(initialNode);

    gridSizeX = grid->getNumCellX();
    gridSizeY = grid->getNumCellY();

    for (size_t y = 0; y < grid->getNumCellY(); y++)
    {
        Node* current = stack.top();
        for (size_t x = 0; x < grid->getNumCellX(); x++)
        {
            Node* n;

            //Y+1
            if (y + 1 < grid->getNumCellY() && !visitedNode[y + 1][x])
            {
                if (y + 1 < grid->getNumCellY())
                    n = new Node(Vector2D(Vector2D(x, y + 1)));

                stack.push(n);
                float _weight = 1 + 100 * !(grid->isValidCell(Vector2D(x, y)));
                connections.push_back(new Connection(current, n, _weight));
                visitedNode[y + 1][x] = true;
                current = stack.top();
            }

            //Y-1
            if (y - 1 != -1)
            {
                if (!visitedNode[y - 1][x])
                {
                    if (y - 1 >= 0)
                        n = new Node(Vector2D(Vector2D(x, y - 1)));

                    stack.push(n);
                    float _weight = 1 + 100 * !(grid->isValidCell(Vector2D(x, y)));
                    connections.push_back(new Connection(current, n, _weight));
                    visitedNode[y - 1][x] = true;
                    current = stack.top();
                }
            }

            //X+1
            if(x + 1 < grid->getNumCellX() && !visitedNode[y][x + 1])
            {
                if (x + 1 < grid->getNumCellX())
                    n = new Node(Vector2D(Vector2D(x + 1, y)));

                stack.push(n);
                float _weight = 1 + 100 * !(grid->isValidCell(Vector2D(x, y)));
                connections.push_back(new Connection(current, n, _weight));
                visitedNode[y][x + 1] = true;
                current = stack.top();
            }

            //X-1
            if (x - 1 >= 0 && !visitedNode[y][x - 1])
            {
                if (x - 1 >= 0)
                    n = new Node(Vector2D(Vector2D(x - 1, y)));

                stack.push(n);
                float _weight = 1 + 100 * !(grid->isValidCell(Vector2D(x, y)));
                connections.push_back(new Connection(current, n, _weight));
                visitedNode[y][x - 1] = true;
                current = stack.top();
            }

            //X+1 Y+1

            //X+1 Y-1

            //X-1 Y+1

            //X-1 Y-1
        }
    }
    delete(visitedNode);
}