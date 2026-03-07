#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Scene.h"

int main()
{
    if (!glfwInit()) {
        std::cout << "Failed to init GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    Scene scene;
    scene.Init();

    float lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {

        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        scene.Update(deltaTime);
        scene.Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    scene.Destroy();
    glfwTerminate();
}