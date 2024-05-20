#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Config.hpp"

using namespace std;

const string Config::ITD_FILE = "data/config_map.itd";

void Color::setColor(const int &r, const int &g, const int &b, const int &t)
{
    this->red = r;
    this->blue = b;
    this->green = g;
    this->transparency = t;
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
                this->color_path.setColor(stoi(split_line[1]), stoi(split_line[2]), stoi(split_line[3]), stoi(split_line[4]));
            }
            else if (myline.starts_with("in"))
            {
                this->color_in.setColor(stoi(split_line[1]), stoi(split_line[2]), stoi(split_line[3]), stoi(split_line[4]));
            }
            else if (myline.starts_with("out"))
            {
                this->color_out.setColor(stoi(split_line[1]), stoi(split_line[2]), stoi(split_line[3]), stoi(split_line[4]));
            }
            else if (myline.starts_with("graph"))
            {
                nbNodes = stoi(split_line[1]);
            }
            else if (myline.starts_with("node"))
            {
                Node node(stoi(split_line[0]), stoi(split_line[1]), stoi(split_line[2]));

                if (stoi(split_line[0]) != this->nbNodes - 1)
                {
                    if (stoi(split_line[0]) == 0)
                    {
                        node.setStatus(NodeStatus::Start);
                    }
                    else
                    {
                        node.setStatus(NodeStatus::Path);
                    }
                    for (int i{3}; i < split_line.size(); i++)
                    {
                        node.addNeighbor(stoi(split_line[i]));
                    }
                }

                else
                {
                    node.setStatus(NodeStatus::End);
                }
            }
        }
    }
    else
    {
        cout << "Couldn't open file\n";
    }
}

vector<string> split_string(string str)
{
    stringstream ss(str);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string> split_line(begin, end);
    return split_line;
}
