// glad обов'язково підключається ДО glfw3.h
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ViewerWindow.h"

#include <stdexcept>

// ---- C-подібні колбеки для GLFW ----

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto* self = static_cast<ViewerWindow*>(glfwGetWindowUserPointer(window));
    if (self && self->m_keyCallback)
    {
        self->m_keyCallback(static_cast<KeyCode>(key),
                            static_cast<Action>(action),
                            static_cast<Modifier>(mods));
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    auto* self = static_cast<ViewerWindow*>(glfwGetWindowUserPointer(window));
    if (self && self->m_mouseButtonCallback)
    {
        self->m_mouseButtonCallback(static_cast<ButtonCode>(button),
                                    static_cast<Action>(action),
                                    static_cast<Modifier>(mods));
    }
}

void cursorCallback(GLFWwindow* window, double xpos, double ypos)
{
    auto* self = static_cast<ViewerWindow*>(glfwGetWindowUserPointer(window));
    if (self && self->m_cursorCallback)
        self->m_cursorCallback(xpos, ypos);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    auto* self = static_cast<ViewerWindow*>(glfwGetWindowUserPointer(window));
    if (self && self->m_scrollCallback)
        self->m_scrollCallback(xoffset, yoffset);
}

// ---- Методи класу ----

ViewerWindow::ViewerWindow(const std::string& title, int width, int height)
{
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW");

    m_ptrHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_ptrHandle)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(m_ptrHandle);

    // Завантаження функцій OpenGL (після створення контексту!)
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        glfwDestroyWindow(m_ptrHandle);
        glfwTerminate();
        throw std::runtime_error("Failed to initialize glad");
    }

    glfwSwapInterval(1);

    glfwSetWindowUserPointer(m_ptrHandle, this);
    glfwSetKeyCallback(m_ptrHandle, &keyCallback);
    glfwSetMouseButtonCallback(m_ptrHandle, &mouseButtonCallback);
    glfwSetCursorPosCallback(m_ptrHandle, &cursorCallback);
    glfwSetScrollCallback(m_ptrHandle, &scrollCallback);
}

ViewerWindow::~ViewerWindow()
{
    if (m_ptrHandle)
        glfwDestroyWindow(m_ptrHandle);
    glfwTerminate();
}

void ViewerWindow::setKeyCallback(KeyCallback callback)               { m_keyCallback = std::move(callback); }
void ViewerWindow::setMouseButtonCallback(MouseButtonCallback callback) { m_mouseButtonCallback = std::move(callback); }
void ViewerWindow::setCursorCallback(CursorCallback callback)         { m_cursorCallback = std::move(callback); }
void ViewerWindow::setScrollCallback(ScrollCallback callback)         { m_scrollCallback = std::move(callback); }

GLFWwindow* ViewerWindow::getGLFWHandle() const { return m_ptrHandle; }

int ViewerWindow::getWidth() const
{
    int w = 0, h = 0;
    glfwGetFramebufferSize(m_ptrHandle, &w, &h);
    return w;
}

int ViewerWindow::getHeight() const
{
    int w = 0, h = 0;
    glfwGetFramebufferSize(m_ptrHandle, &w, &h);
    return h;
}
