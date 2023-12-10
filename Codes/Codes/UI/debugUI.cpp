#include <Codes/UI/debugUI.h>

#include <Codes/Time/time.h>

#include <Codes/Debug/debugUI.h>

void drawDebugUI() {
    DRAWUITEXT(int(1/Time::getDeltaTime()), Vec2(10, 10), Color(1, 1, 1, 1));

    DRAWUILINE(Vec2(20, 50), Vec2(100, 30), Color(0, 0, 1, 1), 2);
}
