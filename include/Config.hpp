#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Node.hpp"
#include <img/img.hpp>
#include "Graph.hpp"
#include "Tile.hpp"
<<<<<<< HEAD
=======
#include "utils.hpp"

#include <img/img.hpp>
#include <glad/glad.h>
>>>>>>> 2bbbb0f22325beee8920eb12d0a371378f69891e
#include <GLFW/glfw3.h>

using namespace std;

struct Color
{
    int red;
    int green;
    int blue;
    int transparency;

    void setColor(const int &r, const int &g, const int &b, const int &t);
};

struct Pixel
{
    int posX{};
    int posY{};
    Color color{};
    TileType typeChemin{};
};
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
    vector<GLuint> textures{};
    img::Image pixelized_map{img::load(make_absolute_path("/image/map.png", true), 4, false)};

public:
    Color getColorIn();
    Color getColorOut();
    Color getColorPath();
    int getNbNodes();
    vector<Node> getNodes();
    Graph::WeightedGraph getGraph();
    static const string ITD_FILE;
    void itdConfig();
    void getNodesFromItdFile(vector<string> split_line);
    void getColorFromItd(Color &color, vector<string> split_line);
    void createGraphFromNodes();
    void setTextures();
    void imgRead();
};

vector<string> split_string(string str);
unsigned char *getMatchingTexture(TileType type, int &x, int &y, int &n);