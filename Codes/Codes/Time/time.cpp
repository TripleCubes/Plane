#include <Codes/Time/time.h>

#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>
#include <cmath>

float Time::fpsCap = 60;
float Time::frameStartTime = 0;
float Time::deltaTime = 0;
float Time::previousTime = 0;
float Time::frameTime = 0;

void Time::setFrameStartTime() {
    frameStartTime = glfwGetTime();
}

void Time::syncFrame() {
    using namespace std::chrono;
    using namespace std::this_thread;

    frameTime = glfwGetTime() - frameStartTime;
    sleep_for(milliseconds((int)round((1/fpsCap - frameTime)* 1000)));
}

void Time::update() {
    deltaTime = glfwGetTime() - previousTime;
    previousTime = glfwGetTime();
}

float Time::getDeltaTime() {
    return deltaTime;
}

float Time::getCurrentTime() {
    return glfwGetTime();
}

float Time::getFrameTime() {
    return frameTime;
}
