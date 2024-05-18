#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "config_map.hpp"
#include "Map.hpp"
#include "Tile.hpp"

using namespace std;

Map config_map()
{
    ifstream myfile;
    string map_location;
    vector<int> path_color;
    vector<int> in_color;
    vector<int> out_color;
    int nbNodes;
    Map map{};

    myfile.open("Itd/config_map.itd");
    string myline;
    if (myfile.is_open())
    {
        while (myfile)
        {
            getline(myfile, myline);
            cout << myline << '\n';
            stringstream ss(myline);
            istream_iterator<string> begin(ss);
            istream_iterator<string> end;
            vector<string> split_line(begin, end);

            if (myline.starts_with("map"))
            {
                map_location = split_line[1];
            }
            else if (myline.starts_with("path"))
            {
                path_color = {stoi(split_line[1]), stoi(split_line[2]), stoi(split_line[3]), stoi(split_line[4])};
            }
            else if (myline.starts_with("in"))
            {
                in_color = {stoi(split_line[1]), stoi(split_line[2]), stoi(split_line[3]), stoi(split_line[4])};
            }
            else if (myline.starts_with("out"))
            {
                out_color = {stoi(split_line[1]), stoi(split_line[2]), stoi(split_line[3]), stoi(split_line[4])};
            }
            else if (myline.starts_with("graph"))
            {
                nbNodes = stoi(split_line[1]);
            }
            else if (myline.starts_with("node"))
            {
            }
        }
    }
    else
    {
        cout << "Couldn't open file\n";
    }

    return map;
}