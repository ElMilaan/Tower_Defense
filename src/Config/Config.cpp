#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include "Config.hpp"
#include "GLHelpers.hpp"
#include "Color.hpp"
#include "Pixel.hpp"

#include <stb_image/stb_image.h>
#include <img/img.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils.hpp"

using namespace std;

const string Config::ITD_FILE = "../../data/config_map.itd";

vector<string>
split_string(string str)
{
    stringstream ss(str);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string> split_line(begin, end);
    return split_line;
}

Config::Config()
{
    itdConfig();
    createGraphFromNodes();
    imgRead();
    setTextures();
}

Color Config::getColorIn()
{
    return color_in;
}
Color Config::getColorOut()
{
    return color_out;
}
Color Config::getColorPath()
{
    return color_path;
}
int Config::getNbNodes()
{
    return nbNodes;
}
vector<Node> Config::getNodes()
{
    return nodes;
}

Graph::WeightedGraph Config::getGraph()
{
    return graph;
}

unordered_map<TileType, GLuint> Config::getTextures()
{
    return textures;
}

unordered_map<pair<int, int>, Pixel> Config::getPixels()
{
    return pixels;
}

/* --------------------- RECUPERATION DES DONNEES DE L'ITD --------------------- */

void Config::getColorFromItd(Color &color, vector<string> split_line)
{
    color.setColor(stoi(split_line[1]), stoi(split_line[2]), stoi(split_line[3]), stoi(split_line[4]));
}

void Config::getNodesFromItdFile(vector<string> split_line)
{
    Node node(stoi(split_line[1]), stoi(split_line[2]), stoi(split_line[3]));

    if (stoi(split_line[1]) != this->nbNodes - 1)
    {
        if (stoi(split_line[1]) == 0)
        {
            node.setStatus(NodeStatus::Start);
        }
        else
        {
            node.setStatus(NodeStatus::Path);
        }
        for (int i{4}; i < split_line.size(); i++)
        {
            node.addNeighbor(stoi(split_line[i]));
        }
    }
    else
    {
        node.setStatus(NodeStatus::End);
    }
    nodes.push_back(node);
}

void Config::itdConfig()
{
    ifstream my_file;

    my_file.open(this->ITD_FILE);

    string my_line;

    if (my_file.is_open())
    {
        while (my_file)
        {
            getline(my_file, my_line);
            vector<string> split_line = split_string(my_line);

            if (my_line.starts_with("path"))
            {
                getColorFromItd(this->color_path, split_line);
            }
            else if (my_line.starts_with("in"))
            {
                getColorFromItd(this->color_in, split_line);
            }
            else if (my_line.starts_with("out"))
            {
                getColorFromItd(this->color_out, split_line);
            }
            else if (my_line.starts_with("graph"))
            {
                nbNodes = stoi(split_line[1]);
            }
            else if (my_line.starts_with("node"))
            {
                getNodesFromItdFile(split_line);
            }
        }
    }
    else
    {
        cout << "Couldn't open file\n";
    }
}

/* --------------- CONSTRUCTION DU GRAPHE A PARTIR DES NODES RECUPEREES --------------- */

void Config::createGraphFromNodes()
{
    for (Node n : nodes)
    {
        for (int neighbor : n.getNeighbors())
        {
            double dist = n.distanceBetweenNodes(nodes[neighbor]);
            graph.add_directed_edge(n.getId(), neighbor, dist);
        }
    }
}

/* --------------- RECUPERATION DES TEXTURES DANS UN TABLEAU D'ID -------------------- */

pair<TileType, img::Image> getMatchingTexture(TileType type)
{
    switch (type)
    {
    case TileType::Curve:
        return {TileType::Curve, img::Image{img::load(make_absolute_path("images/curve.png", true), 4, false)}};
    case TileType::FourWays:
        return {TileType::FourWays, img::Image{img::load(make_absolute_path("images/four_ways.png", true), 4, false)}};
    case TileType::ThreeWays:
        return {TileType::ThreeWays, img::Image{img::load(make_absolute_path("images/three_ways.png", true), 4, false)}};
    case TileType::Straight:
        return {TileType::Straight, img::Image{img::load(make_absolute_path("images/straight.png", true), 4, false)}};
    }
    return {TileType::Grass, img::Image{img::load(make_absolute_path("images/grass.png", true), 4, false)}};
}

// LECTURE DU SCHEMA DE BASE 16x16

void Config::imgRead()
{
    Color color{};
    for (int i{0}; i < pixelized_map.data_size(); i += pixelized_map.channels_count())
    {
        color.setColor(pixelized_map.data()[i], pixelized_map.data()[i + 1], pixelized_map.data()[i + 2], pixelized_map.data()[i + 3]);
        int x = i / pixelized_map.channels_count() % pixelized_map.width();
        int y = i / pixelized_map.channels_count() / pixelized_map.height();
        Pixel p{x, y, color};
        p.setStatus(color, color_in, color_path, color_out);
        pixels.insert({{x, y}, p});
    }
}

// CHARGEMENT DES TEXTURES DES DIFFERENTES TILES

void Config::setTextures()
{
    cout << endl
         << "Loading...." << endl;
    for (int i{0}; i < 5; i++)
    {
        textures.insert({static_cast<TileType>(i), loadTexture(getMatchingTexture(static_cast<TileType>(i)).second)});
    }
    cout << "Done !";
}

// CREATION DES TILES

void Config::createTiles()
{
    for (pair p : pixels)
    {
        bool isStart{false}, isEnd{false};
        TileType tt;
        switch (p.second.status)
        {
        case PixelStatus::In:
            isStart = true;
            tt = TileType::Straight;
            break;
        case PixelStatus::Out:
            isEnd = true;
            tt = TileType::Straight;
            break;
        case PixelStatus::Path:
            break;
        default:
            tt = TileType::Grass;
            break;
        }
    }
}