#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "Node.hpp"

Node::Node()
{
}

Node::Node(int id, GLfloat x, GLfloat y)
{
    this->id = id;
    this->x;
    this->y;
    this->isBarrage = false;
}

Node::Node(int id, bool isBarrage, GLfloat x, GLfloat y)
{
    this->id = id;
    this->x = x;
    this->y = y;
    this->isBarrage = isBarrage;
}

int Node::getId()
{
    return this->id;
}

NodeStatus Node::getStatus()
{
    return this->status;
}

glm::vec2 Node::getPosition()
{
    return {this->x, this->y};
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

GLfloat Node::distanceBetweenNodes(Node target)
{
    GLfloat diffX{static_cast<GLfloat>(target.getPosition().x - this->x)};
    GLfloat diffY{static_cast<GLfloat>(target.getPosition().y - this->y)};
    return abs(diffX + diffY);
}