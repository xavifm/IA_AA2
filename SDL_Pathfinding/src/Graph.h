#pragma once
#include "Vector2D.h"
#include <vector>
#include "Grid.h"

class Node
{
    Vector2D position;

public:
    Node() : position(NULL) {};
    Node(Vector2D position) : position(position) {};

    Vector2D GetPosition() { return position; }
    void SetPosition(Vector2D pos) { position = pos; }
    bool ComparePosition(Vector2D pos);

    int weight;

    inline bool operator==(const Node& n) const { return (position.x == n.position.x) && (position.y == n.position.y); }
    inline bool operator!=(const Node& n) const { return (position.x != n.position.x) || (position.y != n.position.y); }
};

class Connection
{
    Node* nodeFrom;
    Node* nodeTo;
public:
    Connection(Node* _nodeFrom, Node* _nodeTo, float weight);

    float weight;
    Node* GetNodeFrom() { return nodeFrom; };
    Node* GetNodeTo() { return nodeTo; };

    inline bool operator==(const Vector2D& npos) const;
};

class Graph
{
public:
    Graph(Grid* grid);
    std::vector<Connection*> connections;
    int gridSizeX;
    int gridSizeY;
};