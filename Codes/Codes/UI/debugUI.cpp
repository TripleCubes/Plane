#ifdef DEBUG

#include <Codes/UI/debugUI.h>

#include <Codes/Time/time.h>
#include <Codes/View/camera.h>
#include <Codes/Types/vec2.h>
#include <Codes/Types/vec3.h>
#include <Codes/Globals/pi.h>

#include <Codes/Debug/debugUI.h>

void drawDebugUI() {
    DRAWUITEXT(Vec2(10, 10), int(1/Time::getDeltaTime()), Color(1, 1, 1, 1), false);
    DRAWUITEXT(Vec2(10, 40), int(1/Time::getFrameTime()), Color(1, 1, 1, 1), false);

    auto drawCompass = []() {
        Vec2 origin = Vec2(30, 100);
        Vec2 zVec = Vec2(0, 1);
        Vec2 xVec;
        Vec3 cameraDir = Camera::getDir();
        zVec = zVec.rotateRad(- Vec2::angleRad(Vec2(0, -1), Vec2(cameraDir.x, cameraDir.z)));
        xVec = zVec.rotateRad(- PI/2);
        DRAWUILINE(origin, origin + xVec*20, Color(1, 0, 0, 1), 2);
        DRAWUILINE(origin, origin + zVec*20, Color(0, 0, 1, 1), 2);
    };
    drawCompass();
}

#endif
