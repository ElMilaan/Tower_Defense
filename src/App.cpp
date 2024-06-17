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
    nb_hearts = 5;
    img::Image deco{img::load(make_absolute_path("images/deco.png", true), 4, true)};
    img::Image barrage{img::load(make_absolute_path("images/barrage6464.png", true), 4, true)};
    img::Image heart{img::load(make_absolute_path("images/heart.png", true), 4, true)};
    img::Image tower{img::load(make_absolute_path("images/tower.png", true), 4, true)};
    _deco_texture = loadTexture(deco);
    tile_textures = setTileTextures();
    monster_textures = setMonsterTextures();
    barrage_texture = loadTexture(barrage);
    tower_texture = loadTexture(tower);
    GLuint heart_texture = loadTexture(heart);
    for (int i{0}; i < nb_hearts; i++)
    {
        life.push_back(heart_texture);
    }
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
    ITD::itdTower(towers, tower_texture);

    launch_wave = false;
    current_wave = 0;
    current_tower = 0;
}

void App::update()
{
    current_time = glfwGetTime();

    bank.addMoney(0.02);
    render();

    if (life.size() > 0)
    {
        // Update des Tours
        for (pair p : towers)
        {
            if (p.second.second && current_wave < waves.size())
            {
                for (Monster &m : waves[current_wave].monsters_to_update)
                {
                    p.second.first.update(current_time, m, 16.0f);
                }
            }
        }

        // Update des waves
        if (launch_wave && current_wave < waves.size())
        {
            waves[current_wave].update(current_time, 0.1f, map.getShortestPath(), 16.0f, launch_wave, current_wave, life);
        }

        // Update des barrages
        for (Barrage b : barrages)
        {
            b.update(map.getNodes().at(b.getNodeId()));
        }
    }
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
        // glScalef(0.4f, 0.4f, 0.4f);
        drawTile(t, 16.0f);
        glPopMatrix();
    }

    for (pair p : towers)
    {
        if (p.second.second)
        {
            glPushMatrix();
            drawTower(p.second.first, 16.0f);
            glPopMatrix();
        }
    }

    drawGameLife(life, {-6, 0}, 16.0f);
    glScalef(2.0f, 2.0f, 2.0f);
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

void App::key_callback(int key, int /*scancode*/, int action, int /*mods*/, GLFWwindow *&window)
{
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        // Déclancher les waves
        case GLFW_KEY_W:
            if (!launch_wave)
            {
                launch_wave = true;
            }
            break;
        case GLFW_KEY_B:
            // faire dessiner le barrage
            if (!launch_wave && barrages.size() < map.getBarrageEdges().size())
            {
                Barrage b{barrage_texture};
                if (bank.getBankSold() - b.COST >= 0)
                {
                    map.deployBarrage(b);
                    barrages.push_back(b);
                    map.setVertexesToVisit();
                    bank.removeMoney(b.COST);
                }
            }
            break;
        case GLFW_KEY_T:
            if (!launch_wave && current_tower < towers.size() && bank.getBankSold() - towers.at(current_tower).first.COSTS[0] >= 0)
            {
                towers.at(current_tower).second = true;
                bank.removeMoney(towers.at(current_tower).first.COSTS[0]);
                current_tower++;
            }
            break;
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            cout << "On ferme" << endl;
            break;
        }
    }
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
        glOrtho(-_viewSize / 2.0f * aspectRatio, _viewSize / 2.0f * aspectRatio, -_viewSize / 2.0f, _viewSize / 2.0f, -1.0f, 1.0f);
    }
    else
    {
        glOrtho(-_viewSize / 2.0f, _viewSize / 2.0f, -_viewSize / 2.0f / aspectRatio, _viewSize / 2.0f / aspectRatio, -1.0f, 1.0f);
    }
}
