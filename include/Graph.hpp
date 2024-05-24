#pragma once

#include <vector>
#include <unordered_map>
#include <utility>
#include <functional>

using namespace std;

namespace Graph
{
    struct WeightedGraphEdge
    {
        int to{};
        double weight{1.0f};
        bool isClosed{false};

        void toggleClosed();
        bool operator==(WeightedGraphEdge const &other) const;
        bool operator!=(WeightedGraphEdge const &other) const;
    };

    struct WeightedGraph
    {
        unordered_map<int, vector<WeightedGraphEdge>> adjacency_list{};

        bool exists(int const id);

        void add_vertex(int const id);

        void add_directed_edge(int const from, int const to, double const weight = 1.0f);

        bool operator==(WeightedGraph const &other) const;
        bool operator!=(WeightedGraph const &other) const;

        void print_BFS(int const start) const;

        unordered_map<int, pair<double, int>> dijkstra(int const &start, int const &end);
    };

    WeightedGraph build_from_adjacency_matrix(vector<vector<double>> const &adjacency_matrix);
    void display_shortest_path(unordered_map<int, pair<double, int>> tab, int start, int end);

}

ostream &operator<<(ostream &os, const Graph::WeightedGraph graph);
ostream &operator<<(ostream &os, const vector<vector<double>> adj_mat);
ostream &operator<<(ostream &os, const unordered_map<int, pair<double, int>> map);
bool isIn(const vector<int> &vec, int val);

struct AdjacencyMatrix
{
    vector<vector<double>> matrix;
    void setMatrix();
};