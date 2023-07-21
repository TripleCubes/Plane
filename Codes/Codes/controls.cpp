#include <Codes/controls.h>

#include <Codes/Settings/settings.h>
#include <Codes/View/camera.h>
#include <Codes/input.h>
#include <Codes/Time/time.h>
#include <Codes/Types/vec2.h>
#include <GLFW/glfw3.h>

#include <Codes/Debug/print.h>

extern bool mouseLocked;
extern GLFWwindow *glfwWindow;
extern int currentWindowWidth;
extern int currentWindowHeight;

float Controls::cameraRotationX = 0;
float Controls::cameraRotationY = 0;

void Controls::update() {
    updateSettings();

    if (Settings::isFreeCam()) {
        updateCameraDir();
        updateMovements();
    }

    // placeBreakBlock();
}

void Controls::updateSettings() {
    if (Input::justPressed("M")) {
        Settings::wireframeMode = !Settings::wireframeMode;
    }

    if (Input::justPressed("N")) {
        Settings::perspectiveProjection = !Settings::perspectiveProjection;
    }

    if (Input::justPressed("B")) {
        Settings::freeCam = !Settings::freeCam;
        if (Settings::isFreeCam()) {
            lockMouse();
        } else {
            unlockMouse();
        }
    }
}

void Controls::updateCameraDir() {
    Vec2 mouseMoveOffset = Input::getMouseMoveOffset();

    cameraRotationX -= mouseMoveOffset.y * 0.17;
    if (cameraRotationX > 89.99)
    {
        cameraRotationX = 89.99;
    }
    else if (cameraRotationX < -89.99)
    {
        cameraRotationX = -89.99;
    }
    cameraRotationY -= mouseMoveOffset.x * 0.17;

    Camera::dir = Vec3(0, 0, -1).rotateXY(cameraRotationX, cameraRotationY);
}

void Controls::updateMovements() {
    Vec3 moveDir;
    Vec3 cameraDir = Camera::getDir();
    cameraDir.y = 0;
    cameraDir = cameraDir.normalize();
    Vec3 cameraDirRotated90 = cameraDir.rotateY(90);
    if (Input::pressed("W")) {
        moveDir += cameraDir;
    }
    if (Input::pressed("A")) {
        moveDir += cameraDirRotated90;
    }
    if (Input::pressed("S")) {
        moveDir -= cameraDir;
    }
    if (Input::pressed("D")) {
        moveDir -= cameraDirRotated90;
    }
    if (Input::pressed("SPACE")) {
        moveDir.y += 1;
    }
    if (Input::pressed("LEFT_SHIFT")) {
        moveDir.y -= 1;
    }
    
    if (moveDir != Vec3(0, 0, 0)) {
        Camera::pos += moveDir * 15 * Time::getDeltaTime();
    }
}

void Controls::placeBreakBlock() {

}

void Controls::lockMouse() {
    if (mouseLocked) {
        return;
    }

    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    mouseLocked = true;
}

void Controls::unlockMouse() {
    if (!mouseLocked) {
        return;
    }

    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetCursorPos(glfwWindow, (double)currentWindowWidth/2, (double)currentWindowHeight/2);
    mouseLocked = false;
}
