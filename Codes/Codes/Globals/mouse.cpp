#include <GLFW/glfw3.h>

extern GLFWwindow *glfwWindow;
extern int currentWindowWidth;
extern int currentWindowHeight;
extern bool mouseLocked;

void lockMouse() {
    if (mouseLocked) {
        return;
    }

    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    mouseLocked = true;
}

void unlockMouse() {
    if (!mouseLocked) {
        return;
    }

    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetCursorPos(glfwWindow, (double)currentWindowWidth/2, (double)currentWindowHeight/2);
    mouseLocked = false;
}
