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
#include "Position.hpp"

#include <img/img.hpp>
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

class Config
{
private:
    static const int SCHEMA_DIMENSION{16};
    static const int PIXELS_DIMENSION{1024};
    static const int TILE_DIMENSION{64};
    Color color_in;
    Color color_out;
    Color color_path;
    int nbNodes{};
    vector<Node> nodes{};
    Graph::WeightedGraph graph{};
    string map_string_path{};
    unordered_map<pair<int, int>, Pixel> pixels;
    unordered_map<TileType, GLuint> textures{};
    unordered_map<pair<int, int>, Tile> tiles{};
    img::Image pixelized_map{img::load(make_absolute_path("images/map.png", true), 4, false)};
    const unordered_map<int, pair<TileType, int>> paths_rotations = {
        {0b0101, {TileType::Straight, 0}},    // Haut-Bas
        {0b1010, {TileType::Straight, 90}},   // Droite-Gauche
        {0b0111, {TileType::ThreeWays, 0}},   // Haut-Droite-Bas
        {0b1101, {TileType::ThreeWays, 180}}, // Haut-Bas-Gauche
        {0b1011, {TileType::ThreeWays, 270}}, // Haut-Droite-Gauche
        {0b1110, {TileType::ThreeWays, 90}},  // Droite-Bas-Gauche
        {0b0110, {TileType::Curve, 0}},       // Bas-Droite
        {0b1100, {TileType::Curve, 90}},      // Bas-Gauche
        {0b1001, {TileType::Curve, 180}},     // Haut-Gauche
        {0b0011, {TileType::Curve, 270}},     // Haut-Droite
        {0b1111, {TileType::FourWays, 0}}     // Tous les côtés
    };

public:
    Config();
    Color getColorIn();
    Color getColorOut();
    Color getColorPath();
    int getNbNodes();
    vector<Node> getNodes();
    Graph::WeightedGraph getGraph();
    unordered_map<TileType, GLuint> getTextures();
    unordered_map<pair<int, int>, Pixel> getPixels();
    unordered_map<pair<int, int>, Tile> getTiles();
    static const string ITD_FILE;
    void itdConfig();
    void getNodesFromItdFile(vector<string> split_line);
    void getColorFromItd(Color &color, vector<string> split_line);
    void createGraphFromNodes();
    void imgRead();
    void setTextures();
    void createTiles();
    vector<bool> checkAround(Pixel &p);
    pair<TileType, int> getPathType(Pixel &p);
};

vector<string> split_string(string str);
pair<TileType, img::Image> getMatchingTexture(TileType type);