#pragma once

#include <glad/glad.h>
#include <simpletext.h>
#include <unordered_map>
#include <vector>
#include "Bank.hpp"
#include "Tile.hpp"
#include "Map.hpp"
#include "Monster.hpp"
#include "Wave.hpp"

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
    Bank bank{};
    int _width{};
    int _height{};
    double current_time{};
    double _previousTime{};
    double _viewSize{};
    Map map{};
    bool launch_wave{};
    int current_wave{};
    vector<Wave> waves{};
    GLuint _deco_texture;
    GLuint barrage_texture;
    unordered_map<TileType, GLuint> tile_textures{};
    unordered_map<MonsterType, GLuint> monster_textures{};
    double _angle{};
    SimpleText text_renderer{};
    void render();
    Monster *m{};
};