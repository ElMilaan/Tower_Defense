#include <iostream>
#include <vector>
#include "Location.hpp"

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
    Location location{};
    vector<int> neighbors{};

public:
    Node();
    Node(int id, int x, int y);
    int getId();
    NodeStatus getStatus();
    Location getLocation();
    vector<int> getNeighbors();
    void setStatus(NodeStatus status);
    void addNeighbor(int neighbor);
};
