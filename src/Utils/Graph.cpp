#include <iostream>
#include "Graph.hpp"
#include <stack>
#include <queue>
#include <functional>
#include <vector>

using namespace std;

namespace Graph
{
    bool WeightedGraphEdge::operator==(WeightedGraphEdge const &other) const
    {
        return to == other.to && weight == other.weight;
    }
    bool WeightedGraphEdge::operator!=(WeightedGraphEdge const &other) const
    {
        return !(*this == other);
    }

    bool WeightedGraph::operator==(WeightedGraph const &other) const
    {
        return adjacency_list == other.adjacency_list;
    }

    bool WeightedGraph::operator!=(WeightedGraph const &other) const
    {
        return !(*this == other);
    }

    bool WeightedGraph::exists(int const id)
    {
        return adjacency_list.find(id) != adjacency_list.end();
    }

    void WeightedGraph::clear()
    {
        adjacency_list.clear();
    }

    void WeightedGraph::addVertex(int const id)
    {
        if (!exists(id))
        {
            adjacency_list.insert({id, {}});
        }
    }

    void WeightedGraph::addDirectedEdge(int const from, int const to, double const weight)
    {
        addVertex(from);
        addVertex(to);
        adjacency_list.at(from).push_back({to, weight});
    }

    void WeightedGraph::closeEdge(int const from, int const to)
    {
        for (WeightedGraphEdge wge : adjacency_list.at(from))
        {
            if (wge.to == to)
            {
                wge.isClosed = true;
            }
        }
    }

    WeightedGraph buildFromAdjacencyMatrix(vector<vector<double>> const &adjacency_matrix)
    {
        WeightedGraph graph{};
        for (int i{0}; i < adjacency_matrix.size(); i++)
        {
            graph.addVertex(i + 1);
            for (int j{0}; j < adjacency_matrix[i].size(); j++)
            {
                if (adjacency_matrix[i][j] != 0)
                {
                    graph.addDirectedEdge(i + 1, j + 1, adjacency_matrix[i][j]);
                }
            }
        }
        return graph;
    }

    unordered_map<int, pair<double, int>> WeightedGraph::dijkstra(int const &start, int const &end)
    {
        unordered_map<int, pair<double, int>> tab{};
        tab.insert({start, {0, 1}});
        // On définit la priorité comme décroissante pour avoir le plus petit élément retourné par .top()
        priority_queue<int, std::vector<int>, std::greater<int>> toVisit{};
        toVisit.push(start);
        int current{-1};
        while (!toVisit.empty() && current != end)
        {
            current = toVisit.top();
            toVisit.pop();
            // On parcourt tous les sommets adjacents du sommet courant
            for (WeightedGraphEdge edge : adjacency_list.at(current))
            {
                // On calcul la distance depuis le sommet initial jusqu'à celui-ci
                double newWeight{edge.weight + tab.at(current).first};
                // On vérifie que le sommet n'a pas encore été ajouté ou que la nouvelle distance est plus courte que celle calculée pour ce même sommet précédemment ou que le sommet est accessible (barrage de castor non placé)
                if ((tab.find(edge.to) == tab.end() || newWeight < tab.at(edge.to).first) && !edge.isClosed)
                {
                    // S'il existe déjà (donc que sa distance au sommet initiale est plus coure que celle calculée plus tôt), on supprime le sommet du tableau.
                    if (tab.find(edge.to) != tab.end())
                    {
                        tab.erase(edge.to);
                    }
                    // On insère le nouveau sommet dans le tableau (ou on le réinsert s'il vient d'être supprimé)
                    tab.insert({edge.to, {newWeight, current}});
                    toVisit.push(edge.to);
                }
            }
        }

        return tab;
    }

    vector<int> getNodesIdFromDijkstra(unordered_map<int, pair<double, int>> tab, int start, int end)
    {
        int currentVertex{end};
        vector<int> vertexes{start};

        while (currentVertex != start)
        {
            if (currentVertex != end)
            {
                vertexes.push_back(currentVertex);
            }
            currentVertex = tab.at(currentVertex).second;
        }
        vertexes.push_back(end);
        sort(vertexes.begin(), vertexes.end());

        return vertexes;
    }

    void displayShortestPath(std::unordered_map<int, std::pair<double, int>> tab, int start, int end)
    {
        int currentVertex{end};
        vector<int> vertexes{start};

        while (currentVertex != start)
        {
            if (currentVertex != end)
            {
                vertexes.push_back(currentVertex);
            }
            currentVertex = tab.at(currentVertex).second;
        }
        vertexes.push_back(end);
        sort(vertexes.begin(), vertexes.end());

        for (int v : vertexes)
        {
            cout << "|" << v << "|";
            if (v != end)
            {
                cout << " -> ";
            }
        }

        cout << " (Ponderation totale = " << tab.at(end).first << ")";
    }

}

ostream &operator<<(ostream &os, const Graph::WeightedGraph graph)
{
    for (pair p : graph.adjacency_list)
    {
        for (Graph::WeightedGraphEdge wge : p.second)
        {
            os << "|" << p.first << "| -- " << wge.weight << " -> |" << wge.to << "|" << endl;
        }
    }
    return os;
}

ostream &operator<<(ostream &os, const unordered_map<int, pair<double, int>> map)
{
    for (pair p : map)
    {
        os << "|" << p.first << "| (" << p.second.first << ", |" << p.second.second << "|)" << endl;
    }
    return os;
}

ostream &operator<<(ostream &os, const vector<vector<double>> adj_mat)
{
    for (int i{0}; i < adj_mat.size(); i++)
    {
        os << endl;
        for (int j{0}; j < adj_mat[i].size(); j++)
        {
            os << adj_mat[i][j] << "  ";
        }
    }
    return os;
}

bool isIn(const std::vector<int> &vec, int val)
{
    for (int e : vec)
    {
        if (e == val)
        {
            return true;
        }
    }
    return false;
}