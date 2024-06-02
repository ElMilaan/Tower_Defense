#pragma once

#include <glad/glad.h>
#include <simpletext.h>
#include <unordered_map>
#include "Bank.hpp"
#include "Tile.hpp"

class App
{
public:
    App();
    void setup();
    void update();
    Bank getBank();

    // GLFW callbacks binding
    void key_callback(int key, int scancode, int action, int mods);
    void mouse_button_callback(int button, int action, int mods);
    void scroll_callback(double xoffset, double yoffset);
    void cursor_position_callback(double xpos, double ypos);
    void size_callback(int width, int height);

private:
    static const int MAP_SIZE{16};
    void render();
    Bank bank{};
    int _width{};
    int _height{};
    double _previousTime{};
    double _viewSize{};

    // Add your variables here
    vector<Tile> map_tiles;
    GLuint _deco_texture;
    double _angle{};

    SimpleText TextRenderer{};
};