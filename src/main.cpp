#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include "Graph.hpp"
#include "App.hpp"
#include "Config.hpp"

using namespace std;

namespace
{
    App &window_as_app(GLFWwindow *window)
    {
        return *static_cast<App *>(glfwGetWindowUserPointer(window));
    }
}

// Optional: limit the frame rate
constexpr double TARGET_TIME_FOR_FRAME{1.0 / 60.0};

int main()
{

    // ================================== TESTS ====================================

    Config config{};
    config.itdConfig();

    cout << "Nb nodes : " << config.getNbNodes() << endl;
    cout << "In : ( " << config.getColorIn().red << " , " << config.getColorIn().green << " , " << config.getColorIn().blue << " )" << endl;
    cout << "Path : ( " << config.getColorPath().red << " , " << config.getColorPath().green << " , " << config.getColorPath().blue << " )" << endl;
    cout << "Out : ( " << config.getColorOut().red << " , " << config.getColorOut().green << " , " << config.getColorOut().blue << " )" << endl;

    for (Node n : config.getNodes())
    {
        cout << "( id : " << n.getId() << "; position |" << n.getPosition().getX() << "," << n.getPosition().getY() << "| ; voisins : ";
        for (int nei : n.getNeighbors())
        {
            cout << nei << ", ";
        }
        cout << " )" << endl;
    }

    cout << endl;

    config.createGraphFromNodes();

    cout << config.getGraph();

    // config.setTextures();

    // cout << endl
    //      << endl;

    // cout << "size of textures : " << config.getTextures().size();
    // for (auto a : config.getTextures())
    // {
    //     cout << a << " , ";
    // }

    config.imgRead();

    cout << "pixels size : " << config.getPixels().size() << endl;

    for (Pixel p : config.getPixels())
    {
        cout << "(x=" << p.posX << ",y=" << p.posY << ",color(" << p.color.red << "," << p.color.green << "," << p.color.blue << "," << p.color.transparency << "))" << endl;
    }

    // ===================================================================================

    //     // Set an error callback to display glfw errors
    //     glfwSetErrorCallback([](int error, const char *description)
    //                          { cerr << "Error " << error << ": " << description << endl; });

    //     // Initialize glfw
    //     if (!glfwInit())
    //     {
    //         return -1;
    //     }

    // #ifdef __APPLE__
    //     // We need to explicitly ask for a 3.3 context on Mac
    //     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // #endif

    //     // Create window
    //     GLFWwindow *window{glfwCreateWindow(1280, 720, "Window", nullptr, nullptr)};
    //     if (!window)
    //     {
    //         cerr << "Failed to create window" << endl;
    //         glfwTerminate();
    //         return -1;
    //     }

    //     // Make the window's context current
    //     glfwMakeContextCurrent(window);

    //     // Intialize glad (loads the OpenGL functions)
    //     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    //     {
    //         cerr << "Failed to initialize OpenGL context" << endl;
    //         glfwTerminate();
    //         return -1;
    //     }

    //     App app{};

    //     glfwSetWindowUserPointer(window, &app);

    //     glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
    //                        { window_as_app(window).key_callback(key, scancode, action, mods); });
    //     glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods)
    //                                { window_as_app(window).mouse_button_callback(button, action, mods); });
    //     glfwSetScrollCallback(window, [](GLFWwindow *window, double xoffset, double yoffset)
    //                           { window_as_app(window).scroll_callback(xoffset, yoffset); });
    //     glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xpos, double ypos)
    //                              { window_as_app(window).cursor_position_callback(xpos, ypos); });
    //     glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height)
    //                               { window_as_app(window).size_callback(width, height); });

    //     // Force calling the size_callback of the game to set the right viewport and projection matrix
    //     {
    //         int width, height;
    //         glfwGetWindowSize(window, &width, &height);
    //         app.size_callback(width, height);
    //     }
    //     glEnable(GL_BLEND);
    //     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //     app.setup();

    //     // Loop until the user closes the window
    //     while (!glfwWindowShouldClose(window))
    //     {
    //         // Get time (in second) at loop beginning
    //         double startTime{glfwGetTime()};
    //         app.bank_sold += 0.005;
    //         app.update();

    //         // Swap front and back buffers
    //         glfwSwapBuffers(window);

    //         // Poll for and process events
    //         glfwPollEvents();

    //         // Optional: limit the frame rate
    //         double elapsedTime{glfwGetTime() - startTime};
    //         // wait the remaining time to match the target wanted frame rate
    //         if (elapsedTime < TARGET_TIME_FOR_FRAME)
    //         {
    //             glfwWaitEventsTimeout(TARGET_TIME_FOR_FRAME - elapsedTime);
    //         }
    //     }

    //     glfwTerminate();
    return 0;
}
