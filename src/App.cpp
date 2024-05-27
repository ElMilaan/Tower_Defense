#define GLFW_INCLUDE_NONE

#include "App.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>

#include "simpletext.h"
#include "utils.hpp"
#include "GLHelpers.hpp"

#include "Bank.hpp"
#include "Config.hpp"

Bank App::getBank()
{
    return bank;
}

App::App() : _previousTime(0.0), _viewSize(2.0)
{
    // load what needs to be loaded here (for example textures)

    img::Image deco{img::load(make_absolute_path("images/deco.png", true), 4, true)};
    _texture = loadTexture(deco);
    Config config{};
}

void App::setup()
{
    // Set the clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Setup the text renderer with blending enabled and white text color
    TextRenderer.ResetFont();
    TextRenderer.SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::WHITE);
    TextRenderer.SetColorf(SimpleText::BACKGROUND_COLOR, 1.f, 1.f, 1.f, 1.f);
    TextRenderer.EnableBlending(true);
}

void App::update()
{

    // const double currentTime{glfwGetTime()};
    // const double elapsedTime{currentTime - _previousTime};
    // _previousTime = currentTime;

    // _angle += 10.0f * elapsedTime;
    // _angle = std::fmod(_angle, 360.0f);

    render();
}

void App::render()
{
    // Clear the color and depth buffers of the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glScalef(0.8f, 0.8f, 0.8f);
    glRotatef(_angle, 0.0f, 0.0f, 1.0f);
    draw_quad_with_texture(_texture);
    glPopMatrix();

    std::string bank_amount_text{100};
    std::stringstream stream2{};
    stream2 << std::fixed << " : " << std::setprecision(2) << bank.getBankSold();
    bank_amount_text = stream2.str();

    TextRenderer.Label(bank_amount_text.c_str(), _width / 2.6, _height / 19, SimpleText::CENTER);
    TextRenderer.Label("30", _width / 1.335, _height / 2.5, SimpleText::CENTER);
    TextRenderer.Label("10", _width / 1.335, _height / 2, SimpleText::CENTER);
    TextRenderer.Label("20", _width / 1.335, _height / 1.665, SimpleText::CENTER);

    // Without set precision
    // const std::string angle_label_text { "Angle: " + std::to_string(_angle) };
    // With c++20 you can use std::format
    // const std::string angle_label_text { std::format("Angle: {:.2f}", _angle) };

    // Using stringstream to format the string with fixed precision
    // std::string angle_label_text{};
    // std::stringstream stream{};
    // stream << std::fixed << "Angle: " << std::setprecision(2) << _angle;
    // angle_label_text = stream.str();

    // TextRenderer.Label(angle_label_text.c_str(), _width / 2, _height - 4, SimpleText::CENTER);

    TextRenderer.Render();
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
