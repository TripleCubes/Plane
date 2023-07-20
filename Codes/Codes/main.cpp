#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Codes/GraphicTypes/graphicTypesManager.h>
#include <Codes/input.h>
#include <Codes/Time/time.h>
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

void initOpenGl() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main() {
    initOpenGl();

    Input::init();
    GlobalGraphics::init();
    View::init();

    while (!glfwWindowShouldClose(glfwWindow)) {
        Time::setFrameStartTime();

        glfwPollEvents();
        Input::update();
        Controls::update();

        ChunkLoader::update();

        View::draw();
        glfwSwapBuffers(glfwWindow);

        Time::syncFrame();
        Time::update();
    }

    GraphicTypesManager::releaseAll();
    glfwTerminate();
    PRINTLN("Reached end of main()");

    return 0;
}
