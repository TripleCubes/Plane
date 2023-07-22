#include <Codes/input.h>

#include <GLFW/glfw3.h>
#include <Codes/Types/vec2.h>

#include <Codes/Debug/print.h>

extern GLFWwindow *glfwWindow;

std::unordered_map<std::string, Input::Key> Input::keys;
bool Input::leftPressed = false;
bool Input::leftJustPressed = false;
bool Input::rightPressed = false;
bool Input::rightJustPressed = false;
float Input::mouseMoveOffsetX = 0;
float Input::mouseMoveOffsetY = 0;
bool Input::resetMouseMoveOffset = false;
float Input::mouseScrollOffsetX = 0;
float Input::mouseScrollOffsetY = 0;
bool Input::resetMouseScrollOffset = false;

void Input::addKey(const std::string &keyString, int glfwKey) {
    if (keys.find(keyString) != keys.end()) {
        LINEINFORMATION();
        PRINT(keyString);
        PRINTLN("already added");
        return;
    }

    Key key = {glfwKey, false, false};
    keys.insert(std::make_pair(keyString, key));
}

void Input::updateMouseMoveOffset(float x, float y) {
    mouseMoveOffsetX = x;
    mouseMoveOffsetY = y;
}

void Input::updateMouseScrollOffset(float x, float y) {
    mouseScrollOffsetX = x;
    mouseScrollOffsetY = y;
}

void Input::init() {
    addKey("ESC", GLFW_KEY_ESCAPE);
    addKey("SPACE", GLFW_KEY_SPACE);
    addKey("LEFT_SHIFT", GLFW_KEY_LEFT_SHIFT);

    int currentKey = GLFW_KEY_A;
    for (char c = 65; c <= 90; c++) {
        addKey(std::string(1, c), currentKey);
        currentKey++;
    }
}

void Input::update() {
    for (auto &i: keys) {
        if (glfwGetKey(glfwWindow, i.second.glfwKey) == GLFW_PRESS) {
            if (!i.second.pressed) {
                i.second.justPressed = true;
            } else {
                i.second.justPressed = false;
            }
            i.second.pressed = true;
        } else {
            i.second.pressed = false;
            i.second.justPressed = false;
        }
    }

    if (glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (!leftPressed) {
            leftJustPressed = true;
        } else {
            leftJustPressed = false;
        }
        leftPressed = true;
    } else {
        leftPressed = false;
        leftJustPressed = false;
    }

    if (glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        if (!rightPressed) {
            rightJustPressed = true;
        } else {
            rightJustPressed = false;
        }
        rightPressed = true;
    } else {
        rightPressed = false;
        rightJustPressed = false;
    }

    if (resetMouseMoveOffset) {
        resetMouseMoveOffset = false;
        mouseMoveOffsetX = 0;
        mouseMoveOffsetY = 0;
    }
    if (mouseMoveOffsetX != 0 || mouseMoveOffsetY != 0) {
        resetMouseMoveOffset = true;
    }

    if (resetMouseScrollOffset) {
        resetMouseScrollOffset = false;
        mouseScrollOffsetX = 0;
        mouseScrollOffsetY = 0;
    }
    if (mouseScrollOffsetX != 0 || mouseScrollOffsetY != 0) {
        resetMouseScrollOffset = true;
    }
}

bool Input::pressed(const std::string &key) {
    if (keys.find(key) == keys.end()) {
        LINEINFORMATION();
        PRINT(key);
        PRINTLN("isnt added");
        return false;
    }
    return keys.at(key).pressed;
}

bool Input::justPressed(const std::string &key) {
    if (keys.find(key) == keys.end()) {
        LINEINFORMATION();
        PRINT(key);
        PRINTLN("isnt added");
        return false;
    }
    return keys.at(key).justPressed;
}

Vec2 Input::getMousePos() {
    double x = 0;
    double y = 0;
    glfwGetCursorPos(glfwWindow, &x, &y);
    return Vec2((float)x, (float)y);
}

Vec2 Input::getMouseMoveOffset() {
    return Vec2(mouseMoveOffsetX, mouseMoveOffsetY);
}

Vec2 Input::getMouseScrollOffset() {
    return Vec2(mouseScrollOffsetX * 7, mouseScrollOffsetY * 7);
}

bool Input::pressed(MouseButton mouseButton) {
    if (mouseButton == MouseButton::LEFT) {
        return leftPressed;
    }
    return rightPressed;
}

bool Input::justPressed(MouseButton mouseButton) {
    if (mouseButton == MouseButton::LEFT) {
        return leftJustPressed;
    }
    return rightJustPressed;
}
