#include <iostream>
#include "Barrage.hpp"
#include "Graph.hpp"
#include "Map.hpp"


using namespace std;

int Barrage::getNodeId()
{
    return node_id;
}

string Barrage::getSpritePath()
{
    return sprite_path;
}

void Barrage::setNodeId(int id)
{
    node_id = id;
}

void Barrage::deploy(Map &map, GLuint barrage_texture)
{
    for (Graph::WeightedGraphEdge &wge : map.getBarrageEdges())
    {
        for (int i = 0; i < map.getBarrageEdges().size(); i++)
        {
            if (!map.getBarrageEdges()[i].isClosed)
            {
                map.getBarrageEdges()[i].isClosed = true;
                glPushMatrix();
                glScalef(0.4f, 0.4f, 0.4f);
                drawBarrage(barrage_texture, 16.0f, map.getNodes().at(i));
                glPopMatrix();
                // bank -= barrage.cost;
                break;
            }
            
        }
        
        
    }
}

void Barrage::update(double current_time, float delta_time, GLuint barrage_texture, Node &node)
{
    glPushMatrix();
    glScalef(0.4f, 0.4f, 0.4f);
    drawBarrage(barrage_texture, 16.0f, node);
    glPopMatrix();
}
