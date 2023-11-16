#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <unordered_map>

class Vec2;

enum class MouseButton {
    LEFT,
    RIGHT,
};

class Input {
    friend void onMouseMove(double mousex, double mousey);
    friend void onMouseScroll(double xoffset, double yoffset);

public:
    static void init();
    static void update();

    static bool pressed(const std::string &key);
    static bool justPressed(const std::string &key);

    static Vec2 getMousePos();
    static Vec2 getMouseMoveOffset();
    static Vec2 getMouseScrollOffset();
    static bool pressed(MouseButton mouseButton);
    static bool justPressed(MouseButton mouseButton);
    static bool justReleased(MouseButton mouseButton);

private:
    struct Key 
    {
        int glfwKey = 0;
        bool pressed = false;
        bool justPressed = false;
    };

    static std::unordered_map<std::string, Key> keys;
    static bool leftPressed;
    static bool leftJustPressed;
    static bool leftJustReleased;
    static bool rightPressed;
    static bool rightJustPressed;
    static bool rightJustReleased;

    static void addKey(const std::string &key, int glfwKey);

    static float mouseMoveOffsetX;
    static float mouseMoveOffsetY;
    static bool resetMouseMoveOffset;
    static void updateMouseMoveOffset(float x, float y);

    static float mouseScrollOffsetX;
    static float mouseScrollOffsetY;
    static bool resetMouseScrollOffset;
    static void updateMouseScrollOffset(float x, float y);
};

#endif
