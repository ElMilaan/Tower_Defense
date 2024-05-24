#pragma once

#include <glad/glad.h>
#include <simpletext.h>

class App
{
public:
    App();
    double bank_sold{20};
    void setup();
    void update();

    // GLFW callbacks binding
    void key_callback(int key, int scancode, int action, int mods);
    void mouse_button_callback(int button, int action, int mods);
    void scroll_callback(double xoffset, double yoffset);
    void cursor_position_callback(double xpos, double ypos);
    void size_callback(int width, int height);

private:
    void render();

    int _width{};
    int _height{};
    double _previousTime{};
    double _viewSize{};

    // Add your variables here
    GLuint _texture{};
    double _angle{};

    SimpleText TextRenderer{};
};