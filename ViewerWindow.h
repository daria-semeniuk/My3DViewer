#pragma once

#include <functional>
#include <string>

struct GLFWwindow;

enum class Modifier : int
{
    None    = 0,
    Shift   = 0x0001,
    Control = 0x0002,
    Alt     = 0x0004,
    Super   = 0x0008
};

inline bool hasModifier(Modifier mods, Modifier m)
{
    return (static_cast<int>(mods) & static_cast<int>(m)) != 0;
}

enum class Action : int
{
    Release = 0,
    Press   = 1,
    Repeat  = 2
};

enum class ButtonCode : int
{
    Button_0 = 0, Button_1, Button_2, Button_3,
    Button_4, Button_5, Button_6, Button_7
};

// Значення збігаються з константами GLFW_KEY_* з GLFW/glfw3.h
enum class KeyCode : int
{
    Unknown = -1,
    Space = 32,
    Apostrophe = 39, Comma = 44, Minus = 45, Period = 46, Slash = 47,
    Num0 = 48, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
    Semicolon = 59, Equal = 61,
    A = 65, B, C, D, E, F, G, H, I, J, K, L, M,
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    Escape = 256, Enter = 257, Tab = 258, Backspace = 259,
    Insert = 260, Delete = 261,
    Right = 262, Left = 263, Down = 264, Up = 265,
    PageUp = 266, PageDown = 267, Home = 268, End = 269,
    F1 = 290, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
    LeftShift = 340, LeftControl = 341, LeftAlt = 342, LeftSuper = 343,
    RightShift = 344, RightControl = 345, RightAlt = 346, RightSuper = 347
};

class ViewerWindow
{
public:
    using KeyCallback         = std::function<void(KeyCode, Action, Modifier)>;
    using MouseButtonCallback = std::function<void(ButtonCode, Action, Modifier)>;
    using CursorCallback      = std::function<void(double, double)>;
    using ScrollCallback      = std::function<void(double, double)>;

    ViewerWindow(const std::string& title, int width, int height);
    ~ViewerWindow();

    ViewerWindow(const ViewerWindow&) = delete;
    ViewerWindow& operator=(const ViewerWindow&) = delete;

    void setKeyCallback(KeyCallback callback);
    void setMouseButtonCallback(MouseButtonCallback callback);
    void setCursorCallback(CursorCallback callback);
    void setScrollCallback(ScrollCallback callback);

    GLFWwindow* getGLFWHandle() const;
    int getWidth() const;   // розмір framebuffer у пікселях
    int getHeight() const;

private:
    GLFWwindow* m_ptrHandle = nullptr;

    KeyCallback         m_keyCallback;
    MouseButtonCallback m_mouseButtonCallback;
    CursorCallback      m_cursorCallback;
    ScrollCallback      m_scrollCallback;

    friend void keyCallback(GLFWwindow*, int, int, int, int);
    friend void mouseButtonCallback(GLFWwindow*, int, int, int);
    friend void cursorCallback(GLFWwindow*, double, double);
    friend void scrollCallback(GLFWwindow*, double, double);
};
