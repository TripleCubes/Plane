#include <GLFW/glfw3.h>
#include <Codes/RayCast/blockRayCast.h>

GLFWwindow *glfwWindow;
int currentWindowWidth = 1000;
int currentWindowHeight = 600;
bool mouseLocked = true;
BlockRayCastResult savedBlockRayCastResult;
