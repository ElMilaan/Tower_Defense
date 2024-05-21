#include <iostream>
#include <vector>
#include "../../include/Location.hpp"
#include "../../include/Node.hpp"

Node::Node()
{
}

Node::Node(int id, int x, int y)
{
    this->id = id;
    this->location.setX(x);
    this->location.setY(y);
    this->location.setIsPath(true);
}

int Node::getId()
{
    return this->id;
}

NodeStatus Node::getStatus()
{
    return this->status;
}

Location Node::getLocation()
{
    return this->location;
}

vector<int> Node::getNeighbors()
{
    return this->neighbors;
}

void Node::setStatus(NodeStatus status)
{
    this->status = status;
}

void Node::addNeighbor(int neighbor)
{
    this->neighbors.push_back(neighbor);
}