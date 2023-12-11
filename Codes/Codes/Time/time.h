#ifndef TIME_H
#define TIME_H

class Time {
public:
    static void setFrameStartTime();
    static void syncFrame();
    static void update();

    static float getDeltaTime();
    static float getCurrentTime();
    static float getFrameTime();

private:
    static float fpsCap;
    static float frameStartTime;
    static float deltaTime;
    static float previousTime;
    static float frameTime;
};

#endif
