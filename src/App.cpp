#define GLFW_INCLUDE_NONE

#include "App.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include "simpletext.h"
#include "utils.hpp"
#include "Draw.hpp"
#include "GLHelpers.hpp"
#include "Tile.hpp"

#include "Bank.hpp"
#include "Map.hpp"
#include "Itd.hpp"
#include "Wave.hpp"
#include "Monster.hpp"

#include "Barrage.hpp"

Bank App::getBank()
{
    return bank;
}

App::App() : _previousTime(0.0), _viewSize(2.0)
{
    img::Image deco{img::load(make_absolute_path("images/deco.png", true), 4, true)};
    _deco_texture = loadTexture(deco);
    tile_textures = setTileTextures();
    monster_textures = setMonsterTextures();
}

void App::setup()
{
    // Set the clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Setup the text renderer with blending enabled and white text color
    text_renderer.ResetFont();
    text_renderer.SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::WHITE);
    text_renderer.SetColorf(SimpleText::BACKGROUND_COLOR, 1.f, 1.f, 1.f, 1.f);
    text_renderer.EnableBlending(true);

    // Config de la map
    ITD::itdMap(map);
    map.createGraphFromNodes();
    map.setBarrageEdges();
    map.setVertexesToVisit();
    map.imgRead();
    map.createTiles(tile_textures);

    ITD::itdWave(waves, monster_textures);

    for (Wave w : waves)
    {
        w.display();
        cout << endl;
    }

    // Barrage b{}, b1{}, b2{}, b3{};
    // b.setNodeId(3);
    // b1.setNodeId(8);
    // b2.setNodeId(13);
    // b3.setNodeId(18);
    // map.deployBarrage(b);
    // map.deployBarrage(b1);
    // map.deployBarrage(b2);
    // map.deployBarrage(b3);
    // map.setVertexesToVisit();

    // m = new Monster(MonsterType::Orque, monster_textures.at(MonsterType::Orque));
}

void App::update()
{
    const double currentTime{glfwGetTime()};
    const double elapsedTime{currentTime - _previousTime};
    _previousTime = currentTime;

    bank.addMoney(0.02);

    render();

    waves[0].update(currentTime, 0.1f, map.getShortestPath(), 16.0f);

    // m->update(0.1, map.getShortestPath(), 16.0f);
    // cout << m->getPosition().x << " , " << m->getPosition().y << endl;
}

void App::render()
{
    // Clear the color and depth buffers of the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Render de la map
    glPushMatrix();
    for (Tile t : map.getTiles())
    {
        glPushMatrix();
        glScalef(0.4f, 0.4f, 0.4f);
        drawTile(t, 16.0f);
        glPopMatrix();
    }
    glScalef(0.8f, 0.8f, 0.8f);
    draw_quad_with_texture(_deco_texture);
    glPopMatrix();

    std::string bank_amount_text{100};
    std::stringstream stream2{};
    stream2 << std::fixed << " : " << std::setprecision(2) << bank.getBankSold();
    bank_amount_text = stream2.str();

    text_renderer.Label(bank_amount_text.c_str(), _width / 2.6, _height / 19, SimpleText::CENTER);
    text_renderer.Label("30", _width / 1.335, _height / 2.5, SimpleText::CENTER);
    text_renderer.Label("10", _width / 1.335, _height / 2, SimpleText::CENTER);
    text_renderer.Label("20", _width / 1.335, _height / 1.665, SimpleText::CENTER);

    // Without set precision
    // const std::string angle_label_text { "Angle: " + std::to_string(_angle) };
    // With c++20 you can use std::format
    // const std::string angle_label_text { std::format("Angle: {:.2f}", _angle) };

    // Using stringstream to format the string with fixed precision
    // std::string angle_label_text{};
    // std::stringstream stream{};
    // stream << std::fixed << "Angle: " << std::setprecision(2) << _angle;
    // angle_label_text = stream.str();

    // text_renderer.Label(angle_label_text.c_str(), _width / 2, _height - 4, SimpleText::CENTER);

    text_renderer.Render();
}

void App::key_callback(int /*key*/, int /*scancode*/, int /*action*/, int /*mods*/)
{
}

void App::mouse_button_callback(int /*button*/, int /*action*/, int /*mods*/)
{
}

void App::scroll_callback(double /*xoffset*/, double /*yoffset*/)
{
}

void App::cursor_position_callback(double /*xpos*/, double /*ypos*/)
{
}

void App::size_callback(int width, int height)
{
    _width = width;
    _height = height;

    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, _width, _height);

    const double aspectRatio{_width / (double)_height};

    // Change the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (aspectRatio > 1.0f)
    {
        glOrtho(-_viewSize / 5.0f * aspectRatio, _viewSize / 5.0f * aspectRatio, -_viewSize / 5.0f, _viewSize / 5.0f, -1.0f, 1.0f);
    }
    else
    {
        glOrtho(-_viewSize / 5.0f, _viewSize / 5.0f, -_viewSize / 5.0f / aspectRatio, _viewSize / 5.0f / aspectRatio, -1.0f, 1.0f);
    }
}
