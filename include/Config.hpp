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

#include <img/img.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>

using namespace std;

class Config
{
private:
    Color color_in;
    Color color_out;
    Color color_path;
    int nbNodes{};
    vector<Node> nodes{};
    Graph::WeightedGraph graph{};
    string map_string_path{};
    vector<Pixel> pixels{};
    unordered_map<TileType, GLuint> textures{};
    vector<Tile> tiles{};
    img::Image pixelized_map{img::load(make_absolute_path("images/map.png", true), 4, false)};

public:
    Config();
    Color getColorIn();
    Color getColorOut();
    Color getColorPath();
    int getNbNodes();
    vector<Node> getNodes();
    Graph::WeightedGraph getGraph();
    unordered_map<TileType, GLuint> getTextures();
    vector<Pixel> getPixels();
    static const string ITD_FILE;
    void itdConfig();
    void getNodesFromItdFile(vector<string> split_line);
    void getColorFromItd(Color &color, vector<string> split_line);
    void createGraphFromNodes();
    void imgRead();
    void setTextures();
    void createTiles();
};

vector<string> split_string(string str);
pair<TileType, img::Image> getMatchingTexture(TileType type);