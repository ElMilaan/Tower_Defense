#include <iostream>
#include <vector>
#include "Position.hpp"

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
    int id{};
    NodeStatus status{};
    Position position{};
    vector<int> neighbors{};
    bool isBarrage{};

public:
    Node();
    Node(int id, int x, int y);
    Node(int id, bool isBarragePlace, int x, int y);
    int getId();
    NodeStatus getStatus();
    Position getPosition();
    vector<int> getNeighbors();
    void setStatus(NodeStatus status);
    void addNeighbor(int neighbor);
    int distanceBetweenNodes(Node target);
};
