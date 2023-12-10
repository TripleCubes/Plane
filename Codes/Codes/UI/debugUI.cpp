#include <Codes/UI/debugUI.h>

#include <Codes/Time/time.h>

#include <Codes/Debug/debugUI.h>

void drawDebugUI() {
    DRAWUITEXT(int(1/Time::getDeltaTime()), Vec2(10, 10), Color(1, 1, 1, 1));
}
