#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Codes/GraphicTypes/graphicTypesManager.h>
#include <Codes/input.h>
#include <Codes/Time/time.h>
#include <Codes/UI/ui.h>
#include <Codes/Graphics/text.h>
#include <Codes/View/view.h>
#include <Codes/controls.h>
#include <Codes/Chunks/chunkLoader.h>

#include <Codes/Debug/print.h>

extern GLFWwindow *glfwWindow;
extern int currentWindowWidth;
extern int currentWindowHeight;
extern bool mouseLocked;
namespace GlobalGraphics {
    void init();
}

float lastMousePosX = 0;
float lastMousePosY = 0;
bool resetMouseMoveOffset = true;

void onMouseMove(double mousex, double mousey) {
    if (!mouseLocked) {
        resetMouseMoveOffset = true;
        return;
    }

    if (resetMouseMoveOffset) {
        lastMousePosX = mousex;
        lastMousePosY = mousey;
        Input::updateMouseMoveOffset(0, 0);
        resetMouseMoveOffset = false;
        return;
    }
    
    Input::updateMouseMoveOffset(mousex - lastMousePosX, mousey - lastMousePosY);
    lastMousePosX = mousex;
    lastMousePosY = mousey;
}

void onMouseMove(GLFWwindow* window, double mousex, double mousey) {
    onMouseMove(mousex, mousey);
}

void onMouseScroll(double xoffset, double yoffset) {
    Input::updateMouseScrollOffset(xoffset, yoffset);
}

void onMouseScroll(GLFWwindow* window, double xoffset, double yoffset) {
    onMouseScroll(xoffset, yoffset);
}

void initOpenGl() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    glfwWindow = glfwCreateWindow(1000, 600, "Plane", NULL, NULL);
    if (glfwWindow == NULL) {
        LINEINFORMATION();
        PRINTLN("Failed to create window");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(glfwWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LINEINFORMATION();
        PRINTLN("Failed to initialize GLAD");
        return;
    }

    glViewport(0, 0, 1000, 600);

    glfwSetCursorPosCallback(glfwWindow, onMouseMove);
    glfwSetScrollCallback(glfwWindow, onMouseScroll);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_MULTISAMPLE);
}

int main() {
    initOpenGl();

    Input::init();
    GlobalGraphics::init();
    UI::init();
    Text::init();
    View::init();

    ChunkLoader::init();

    while (!glfwWindowShouldClose(glfwWindow)) {
        Time::setFrameStartTime();

        glfwPollEvents();
        Input::update();
        Controls::update();

        UI::update();
        ChunkLoader::update();
        View::update();

        View::draw();
        UI::draw();
        glfwSwapBuffers(glfwWindow);

        Time::syncFrame();
        Time::update();
    }

    GraphicTypesManager::releaseAll();
    glfwTerminate();
    PRINTLN("Reached end of main()");

    return 0;
}
