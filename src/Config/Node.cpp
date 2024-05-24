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
    this->position.setX(x);
    this->position.setY(y);
    this->position.setIsPath(true);
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

double Node::distanceBetweenNodes(Node target)
{
    double diffX{target.getPosition().getX() - this->getPosition().getX()};
    double diffY{target.getPosition().getY() - this->getPosition().getY()};
    return abs(diffX + diffY);
}