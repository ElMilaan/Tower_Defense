#pragma once

#include <iostream>
#include <vector>
#include <img/img.hpp>
#include "Node.hpp"
#include "Graph.hpp"
#include "Tile.hpp"
#include "Color.hpp"
#include "Pixel.hpp"
#include "utils.hpp"
#include "Barrage.hpp"
#include "Tower.hpp"

#include "Monster.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>

using namespace std;

template <>
struct hash<std::pair<int, int>>
{
    std::size_t operator()(const std::pair<int, int> &p) const noexcept
    {
        std::size_t h1 = std::hash<int>{}(p.first);
        std::size_t h2 = std::hash<int>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

enum class Direction
{
    TOP = 1 << 0,
    RIGHT = 1 << 1,
    BOTTOM = 1 << 2,
    LEFT = 1 << 3
};

class Map
{
private:
    Color color_in;
    Color color_out;
    Color color_path;
    int nb_nodes{};
    unordered_map<int, Node> nodes{};
    vector<Graph::WeightedGraphEdge> edges_barrage{};
    Graph::WeightedGraph graph{};
    vector<Node> shortest_path{};
    unordered_map<pair<int, int>, Pixel> pixels;
    vector<Tile> tiles{};
    img::Image pixelized_map{img::load(make_absolute_path("images/map.png", true), 4, true)};
    const unordered_map<int, pair<TileType, int>> paths_rotations = {
        {0b0101, {TileType::Straight, 0}},    // Haut-Bas
        {0b1010, {TileType::Straight, 90}},   // Droite-Gauche
        {0b0111, {TileType::ThreeWays, 0}},   // Haut-Droite-Bas
        {0b1101, {TileType::ThreeWays, 180}}, // Haut-Bas-Gauche
        {0b1011, {TileType::ThreeWays, 270}}, // Haut-Droite-Gauche
        {0b1110, {TileType::ThreeWays, 90}},  // Droite-Bas-Gauche
        {0b0110, {TileType::Curve, 270}},     // Bas-Droite
        {0b1100, {TileType::Curve, 180}},     // Bas-Gauche
        {0b1001, {TileType::Curve, 90}},      // Haut-Gauche
        {0b0011, {TileType::Curve, 0}},       // Haut-Droite
        {0b1111, {TileType::FourWays, 0}}     // Tous les côtés
    };

public:
    Color getColorIn();
    Color getColorOut();
    Color getColorPath();
    int getNbNodes();
    unordered_map<int, Node> getNodes();
    Graph::WeightedGraph getGraph();
    unordered_map<pair<int, int>, Pixel> getPixels();
    vector<Tile> getTiles();
    vector<Node> getShortestPath();
    vector<Graph::WeightedGraphEdge> getBarrageEdges();

    void setColorIn(Color in);
    void setColorOut(Color out);
    void setColorPath(Color path);
    void setNbNodes(int nb_nodes);
    void setBarrageEdges();
    void addNode(Node n);

    void createGraphFromNodes();
    void deployTower(Tower &t);
    void deployBarrage(Barrage &b);
    vector<Node> convertIdToNodes(vector<int> vec);
    void setVertexesToVisit();
    void imgRead();
    void createTiles(unordered_map<TileType, GLuint> &textures);
    vector<bool> checkAround(Pixel &p);
    pair<TileType, int> getPathType(Pixel &p);
};

vector<string> splitString(string str);
pair<TileType, img::Image> getMatchingTileTexture(TileType type);
pair<MonsterType, img::Image> getMatchingMonsterTexture(MonsterType type);