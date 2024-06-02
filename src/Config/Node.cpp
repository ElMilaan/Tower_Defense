#include <iostream>
#include <vector>
#include "Position.hpp"
#include "Node.hpp"

Node::Node()
{
}

Node::Node(int id, int x, int y)
{
    this->id = id;
    this->position.x;
    this->position.y;
    this->position.isPath;
}

int Node::getId()
{
    return this->id;
}

NodeStatus Node::getStatus()
{
    return this->status;
}

Position Node::getPosition()
{
    return this->position;
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

int Node::distanceBetweenNodes(Node target)
{
    int diffX{target.getPosition().x - (int)this->getPosition().x};
    int diffY{target.getPosition().y - (int)this->getPosition().y};
    return abs(diffX + diffY);
}