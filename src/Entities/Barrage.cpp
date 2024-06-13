#include <iostream>
#include "Barrage.hpp"
#include "Graph.hpp"

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

// void Barrage::deploy(Map &map)
// {
//     if (map.graph.adjency_list.at(1).isclosed == true)
//     {
//         // A FAIRE
//         if (map.nodes(8).isclosed == true)
//         {
//             // A FAIRE
//             if (map.nodes(13).isclosed == true)
//             {
//                 // A FAIRE
//                 if (map.nodes(18).isclosed == true)
//                 {
//                     // A FAIRE
//                 }
//                 else
//                 {
//                     map.nodes(18).isclosed = true;
//                     glPushMatrix();
//                     glScalef(0.4f, 0.4f, 0.4f);
//                     drawBarrage(*this, 16.0f);
//                     glPopMatrix();
//                 }
//             }
//             else
//             {
//                 map.nodes(13).isclosed = true;
//                 glPushMatrix();
//                 glScalef(0.4f, 0.4f, 0.4f);
//                 drawBarrage(*this, 16.0f);
//                 glPopMatrix();
//             }
//         }
//         else
//         {
//             map.nodes(8).isclosed = true;
//             glPushMatrix();
//             glScalef(0.4f, 0.4f, 0.4f);
//             drawBarrage(*this, 16.0f);
//             glPopMatrix();
//         }
//     }
//     else
//     {
//         map.nodes(3).isclosed = true;
//         glPushMatrix();
//         glScalef(0.4f, 0.4f, 0.4f);
//         drawBarrage(*this, 16.0f);
//         glPopMatrix();
//     }
// }