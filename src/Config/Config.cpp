#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "../../include/Config.hpp"

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

void getColorFromItd(Color &color, vector<string> split_line)
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
