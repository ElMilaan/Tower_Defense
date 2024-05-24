#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include "Config.hpp"

#include <stb_image/stb_image.h>
#include <img/img.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

const string Config::ITD_FILE = "../../data/config_map.itd";

void Color::setColor(const int &r, const int &g, const int &b, const int &t)
{
    this->red = r;
    this->blue = b;
    this->green = g;
    this->transparency = t;
}

vector<string> split_string(string str)
{
    stringstream ss(str);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string> split_line(begin, end);
    return split_line;
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

void Config::map_config()
{
    ifstream myfile;

    myfile.open(this->ITD_FILE);

    string myline;

    if (myfile.is_open())
    {
        while (myfile)
        {
            getline(myfile, myline);
            vector<string> split_line = split_string(myline);

            if (myline.starts_with("path"))
            {
                getColorFromItd(this->color_path, split_line);
            }
            else if (myline.starts_with("in"))
            {
                getColorFromItd(this->color_in, split_line);
            }
            else if (myline.starts_with("out"))
            {
                getColorFromItd(this->color_out, split_line);
            }
            else if (myline.starts_with("graph"))
            {
                nbNodes = stoi(split_line[1]);
            }
            else if (myline.starts_with("node"))
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

unsigned char *getMatchingTexture(TileType type, int &x, int &y, int &n)
{
    switch (type)
    {
    case TileType::Grass:
        return stbi_load("/images/grass.png", &x, &y, &n, 0);
    case TileType::Curve:
        return stbi_load("/images/curve.png", &x, &y, &n, 0);
    case TileType::FourWays:
        return stbi_load("/images/four_ways.png", &x, &y, &n, 0);
    case TileType::ThreeWays:
        return stbi_load("/images/three_ways.png", &x, &y, &n, 0);
    case TileType::Straight:
        return stbi_load("/images/straight.png", &x, &y, &n, 0);
    }
}

void Config::setTextures()
{
    vector<GLuint> textures(sizeof(TileType));

    for (int i{0}; i < sizeof(TileType); i++)
    {
        int x{}, y{}, n{};
        unsigned char *texture{getMatchingTexture(static_cast<TileType>(i), x, y, n)};

        glGenTextures(1, &textures[i]);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
    }
}