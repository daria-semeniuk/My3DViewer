#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

#include <exception>
#include <iostream>

#include "GeometryPrimitives.h"
#include "OpenglRenderSystem.h"
#include "ViewerWindow.h"

enum class Shape { Cube, Pyramid };
static Shape g_shape = Shape::Pyramid;

void renderScene(OpenglRenderSystem& rs)
{
    static const auto& cube    = GeometryPrimitives::createCubeVertices();
    static const auto& pyramid = GeometryPrimitives::createPyramidVertices();

    rs.renderTriangleSoup(g_shape == Shape::Cube ? cube : pyramid);
}

void moveCube(OpenglRenderSystem& rs, glm::vec3 offset)
{
    rs.setViewMatrix(glm::translate(rs.getViewMatrix(), offset));
}

int main()
{
    try
    {
        constexpr int width  = 640;
        constexpr int height = 480;

        OpenglRenderSystem rs;
        ViewerWindow window("myWindow", width, height);

        constexpr float step = 0.1f;

        window.setKeyCallback([&rs, &window](KeyCode key, Action action, Modifier mods)
        {
            if (action == Action::Release)
                return;

            switch (key)
            {
            case KeyCode::Up:    moveCube(rs, { 0.0f,  step, 0.0f}); break;
            case KeyCode::Down:  moveCube(rs, { 0.0f, -step, 0.0f}); break;
            case KeyCode::Left:  moveCube(rs, { step, 0.0f, 0.0f}); break;
            case KeyCode::Right: moveCube(rs, {-step, 0.0f, 0.0f}); break;
            case KeyCode::Num1:  g_shape = Shape::Cube;    break;
            case KeyCode::Num2:  g_shape = Shape::Pyramid; break;
            case KeyCode::Escape: glfwSetWindowShouldClose(window.getGLFWHandle(), GLFW_TRUE); break;
            default: break;
            }
        });

        rs.init();

        // Світло з прикладу лабораторної: rs.setupLight(0, {0,5,0}, {1,0,0}, {0,1,0}, {0,0,1});
        // Біле світло краще показує кольори граней:
        rs.setupLight(0, glm::vec3(0, 5, 0), glm::vec3(0.3f), glm::vec3(1.0f), glm::vec3(1.0f));
        rs.turnLight(0, true);

        // Камера
        glm::vec3 cameraPosition(0.0f, 0.0f, -3.0f);
        glm::vec3 lookAtCenter(0.0f, 0.0f, 0.0f);
        glm::vec3 cameraUpVector(0.0f, 1.0f, 0.0f);
        rs.setViewMatrix(glm::lookAt(cameraPosition, lookAtCenter, cameraUpVector));

        while (!glfwWindowShouldClose(window.getGLFWHandle()))
        {
            const int w = window.getWidth();
            const int h = window.getHeight();

            rs.setViewport(0, 0, w, h);
            if (h > 0)
                rs.setProjectionMatrix(glm::perspective(glm::radians(60.0f), float(w) / float(h), 0.1f, 500.f));

            rs.clearDisplay(0.5f, 0.5f, 0.5f);
            renderScene(rs);

            glfwSwapBuffers(window.getGLFWHandle());
            glfwWaitEvents();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
