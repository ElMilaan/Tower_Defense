#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Node.hpp"
#include <img/img.hpp>
#include "Graph.hpp"
#include "Tile.hpp"
#include "utils.hpp"

#include <img/img.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>

using namespace std;

enum class PixelStatus
{
    Grass,
    Path,
    In,
    Out
};

struct Color
{
    int red;
    int green;
    int blue;
    int transparency;

    void setColor(const int &r, const int &g, const int &b, const int &t);
    bool isEqualTo(Color c);
    bool isOut(Color out_color);
    bool isIn(Color in_color);
    bool isPath(Color path_color);
};

bool operator==(Color const &c1, Color const &c2);

struct Pixel
{
    int posX{};
    int posY{};
    Color color{};
    PixelStatus status{};

    void setStatus(Color c, Color in_color, Color path_color, Color out_color);
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
    unordered_map <TileType, GLuint> textures{};
    img::Image pixelized_map{img::load(make_absolute_path("images/map.png", true), 4, false)};

public:
    Config();
    Color getColorIn();
    Color getColorOut();
    Color getColorPath();
    int getNbNodes();
    vector<Node> getNodes();
    Graph::WeightedGraph getGraph();
    unordered_map<TileType, GLuint> getTextures();
    vector<Pixel> getPixels();
    static const string ITD_FILE;
    void itdConfig();
    void getNodesFromItdFile(vector<string> split_line);
    void getColorFromItd(Color &color, vector<string> split_line);
    void createGraphFromNodes();
    void setTextures();
    void imgRead(); 
};

vector<string> split_string(string str);
pair<TileType, img::Image> getMatchingTexture(TileType type);