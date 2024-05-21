#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Node.hpp"

using namespace std;

struct Color
{
    int red;
    int green;
    int blue;
    int transparency;

    void setColor(const int &r, const int &g, const int &b, const int &t);
};

class Config
{
private:
    Color color_in;
    Color color_out;
    Color color_path;
    string map_string_path{};
    int nbNodes{};
    vector<Node> nodes{};

public:
    Color getColorIn();
    Color getColorOut();
    Color getColorPath();
    int getNbNodes();
    vector<Node> getNodes();
    static const string ITD_FILE;
    void map_config();
    void getNodesFromItdFile(vector<string> split_line);
};

vector<string> split_string(string str);