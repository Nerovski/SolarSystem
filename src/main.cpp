#include "utilities/Time.h"
#include "utilities/Input.h"
#include "utilities/Window.h"
#include "scenes/MainScene.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include <iostream>
#include <fstream>

// Global objects
Time g_Time;
Input g_Input;
Window g_Window;

int main(int argc, char* argv[]) {
    // Initialize OpenGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Create window
    g_Window.Initialize(glfwCreateWindow(1920, 1080, "SolarSystem", nullptr, nullptr), 2880, 1800);
    if (!g_Window) {
        glfwTerminate();
        std::cout << "Failed to create GLFW window\n";
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(g_Window);
    
    // Load glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return EXIT_FAILURE;
    }
    
    // Set callbacks
    glfwSetFramebufferSizeCallback(g_Window, framebuffer_size_callback);
    glfwSetCursorPosCallback(g_Window, mouse_callback);
    glfwSetScrollCallback(g_Window, scroll_callback);
    
    // Capture the mouse
    glfwSetInputMode(g_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Main scene
    MainScene MainScene;
    MainScene.CreateScene();
    
    MainScene.PreRun();
    MainScene.Run();
    MainScene.PostRun();
    
    // End of application
    glfwSetWindowShouldClose(g_Window, true);
    glfwTerminate();
    return EXIT_SUCCESS;
}
