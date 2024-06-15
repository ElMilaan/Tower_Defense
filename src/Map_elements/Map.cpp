#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include "Map.hpp"
#include "GLHelpers.hpp"
#include "Color.hpp"
#include "Pixel.hpp"
#include "Graph.hpp"
#include "Barrage.hpp"

#include <stb_image/stb_image.h>
#include <img/img.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils.hpp"

using namespace std;

/* ------------------------- GETTERS ----------------------------*/

Color Map::getColorIn()
{
    return color_in;
}
Color Map::getColorOut()
{
    return color_out;
}
Color Map::getColorPath()
{
    return color_path;
}
int Map::getNbNodes()
{
    return nb_nodes;
}
unordered_map<int, Node> Map::getNodes()
{
    return nodes;
}

Graph::WeightedGraph Map::getGraph()
{
    return graph;
}

unordered_map<pair<int, int>, Pixel> Map::getPixels()
{
    return pixels;
}

vector<Tile> Map::getTiles()
{
    return tiles;
}

vector<Node> Map::getShortestPath()
{
    return shortest_path;
}

vector<Graph::WeightedGraphEdge> Map::getBarrageEdges()
{
    return edges_barrage;
};

/* --------------------- SETTERS ----------------------*/

void Map::setColorIn(Color in)
{
    this->color_in = in;
}
void Map::setColorOut(Color out)
{
    this->color_out = out;
}
void Map::setColorPath(Color path)
{
    this->color_path = path;
}
void Map::setNbNodes(int nb_nodes)
{
    this->nb_nodes = nb_nodes;
}
void Map::addNode(Node n)
{
    this->nodes.insert({n.getId(), n});
}

/* --------------- CONSTRUCTION DU GRAPHE A PARTIR DES NODES RECUPEREES --------------- */

void Map::createGraphFromNodes()
{
    graph.clear();
    for (pair p : nodes)
    {
        for (int neighbor : p.second.getNeighbors())
        {
            double dist = p.second.distanceBetweenNodes(nodes[neighbor]);
            graph.addDirectedEdge(p.first, neighbor, dist);
        }
    }
}

void Map::deployBarrage(Barrage &b)
{
    for (Graph::WeightedGraphEdge &wge : edges_barrage)
    {
        if (!wge.isClosed)
        {
            wge.isClosed = true;
            for (Graph::WeightedGraphEdge &wge_g : graph.adjacency_list.at(wge.to - 2))
            {
                if (wge_g.to == wge.to)
                {
                    wge_g.isClosed = true;
                    b.setNodeId(wge.to);
                }
            }
            glPushMatrix();
            // glScalef(0.4f, 0.4f, 0.4f);
            drawBarrage(b.getTexture(), 16.0f, nodes.at(wge.to));
            glPopMatrix();
            break;
        }
    }
}

void Map::setBarrageEdges()
{
    for (pair p : graph.adjacency_list)
    {
        for (Graph::WeightedGraphEdge &wge : p.second)
        {
            if (wge.to == 3 or wge.to == 8 or wge.to == 13 or wge.to == 18)
            {
                edges_barrage.push_back(wge);
            }
        }
    }
}

vector<Node> Map::convertIdToNodes(vector<int> vec)
{
    vector<Node> result;
    for (int i : vec)
    {
        result.push_back(nodes.at(i));
    }
    return result;
}

void Map::setVertexesToVisit()
{
    int start{nodes[0].getId()};
    int end{nodes[nb_nodes - 1].getId()};
    unordered_map<int, pair<double, int>> dij{graph.dijkstra(start, end)};
    shortest_path = convertIdToNodes(Graph::getNodesIdFromDijkstra(dij, start, end));
    for (Node n : shortest_path)
    {
        cout << n.getId() << " , ";
    }
    cout << endl;
}

// LECTURE DU SCHEMA DE BASE 16x16

void Map::imgRead()
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

// CREATION DES TILES

// retourne un vecteur -> 0 = top, 1 = right, 2 = bottom, 3 = left. true si c'est un chemin, false sinon
vector<bool> Map::checkAround(Pixel &p)
{
    vector<bool> around{};
    // on manipule les pixels de chemin, d'entrée et de sortie comme des chemins pour notre condition
    ((pixels.at({p.posX, p.posY + 1}).status == PixelStatus::Path) || (pixels.at({p.posX, p.posY + 1}).status == PixelStatus::In) || (pixels.at({p.posX, p.posY + 1}).status == PixelStatus::Out)) ? around.push_back(true) : around.push_back(false); // top
    ((pixels.at({p.posX + 1, p.posY}).status == PixelStatus::Path) || (pixels.at({p.posX + 1, p.posY}).status == PixelStatus::In) || (pixels.at({p.posX + 1, p.posY}).status == PixelStatus::Out)) ? around.push_back(true) : around.push_back(false); // right
    ((pixels.at({p.posX, p.posY - 1}).status == PixelStatus::Path) || (pixels.at({p.posX, p.posY - 1}).status == PixelStatus::In) || (pixels.at({p.posX, p.posY - 1}).status == PixelStatus::Out)) ? around.push_back(true) : around.push_back(false); // bottom
    ((pixels.at({p.posX - 1, p.posY}).status == PixelStatus::Path) || (pixels.at({p.posX - 1, p.posY}).status == PixelStatus::In) || (pixels.at({p.posX - 1, p.posY}).status == PixelStatus::Out)) ? around.push_back(true) : around.push_back(false); // left
    return around;
}

// retourne le type de chemin + le coeff de rotation pour la sprite lors du rendu
pair<TileType, int> Map::getPathType(Pixel &p)
{
    vector<bool> around{checkAround(p)};
    int mask = 0;
    if (around[0])
        mask |= int(Direction::TOP);
    if (around[1])
        mask |= int(Direction::RIGHT);
    if (around[2])
        mask |= int(Direction::BOTTOM);
    if (around[3])
        mask |= int(Direction::LEFT);

    return paths_rotations.at(mask);
}

void Map::createTiles(unordered_map<TileType, GLuint> &textures)
{
    for (pair p : pixels)
    {
        if ((p.first.first == 7 && p.first.second == 1) || (p.first.first == 7 && p.first.second == 14))
        {
            bool a = true;
        }
        bool isStart{false}, isEnd{false};
        pair<TileType, int> type_and_rotation;
        switch (p.second.status)
        {
        case PixelStatus::In:
            isStart = true;
            type_and_rotation = {TileType::Straight, 0};
            break;
        case PixelStatus::Out:
            isEnd = true;
            type_and_rotation = {TileType::Straight, 0};
            break;
        case PixelStatus::Path:
            type_and_rotation = getPathType(p.second);
            break;
        default:
            type_and_rotation = {TileType::Grass, 0};
            break;
        }
        tiles.push_back({static_cast<GLfloat>(p.second.posX), static_cast<GLfloat>(p.second.posY), textures.at(type_and_rotation.first), type_and_rotation.first, static_cast<GLfloat>(type_and_rotation.second)});
    }
}