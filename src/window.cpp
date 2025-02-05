#include "window.h"

#include <stdexcept>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace fr {
void error_callback(int error, const char* description) {
    std::cerr << "Error: " << description << std::endl;
}


Window::Window() {
    if (!glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW\n");
    }
    glfwSetErrorCallback(error_callback);
    window_ = glfwCreateWindow(1920, 1080, "FoveatedRenderer", nullptr, nullptr);
    if (!window_) {
        glfwTerminate();

        throw std::runtime_error("Could not create window\n");
    }
    glfwMakeContextCurrent(reinterpret_cast<GLFWwindow*>(window_));
    if (!gladLoadGL()) {
        glfwDestroyWindow(reinterpret_cast<GLFWwindow*>(window_));
        glfwTerminate();

        throw std::runtime_error("Failed to load OpenGL\n");
    }
}

Window::~Window() {
    if (window_) {
        glfwDestroyWindow(reinterpret_cast<GLFWwindow*>(window_));
    }
    glfwTerminate();
}

void Window::MainLoop() {
    while (!glfwWindowShouldClose(reinterpret_cast<GLFWwindow*>(window_))) {
        glfwPollEvents();
    }
}

} // namespace fr
