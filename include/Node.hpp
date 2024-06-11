#pragma once

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

enum class NodeStatus
{
    Start,
    End,
    Path
};

class Node
{
private:
    GLfloat x;
    GLfloat y;
    int id{};
    NodeStatus status{};
    vector<int> neighbors{};
    bool isBarrage{};

public:
    Node();
    Node(int id, GLfloat x, GLfloat y);
    Node(int id, bool isBarrage, GLfloat x, GLfloat y);
    int getId();
    glm::vec2 getPosition();
    NodeStatus
    getStatus();
    vector<int> getNeighbors();
    void setStatus(NodeStatus status);
    void addNeighbor(int neighbor);
    GLfloat distanceBetweenNodes(Node target);
};
