#ifndef CONTROLS_H
#define CONTROLS_H

#include <vector> // TEST
#include <Codes/Types/vec2.h> // TEST
#include <Codes/Types/intPos.h> // TEST

class Controls {
public:
    static void init();
    static void update();

private:
    static void updateSettings();
    static void updateCameraDir();
    static void updateMovements();
    static void updatePlaceBreak();
    static void updateChunkPlacing();
    static void updateGameSelection();

    static void updateDebugLogKeys();
    static std::vector<Vec2> highlights; // TEST
    static IntPos startPos; // TEST
    static IntPos endPos; // TEST

    static float cameraRotationX;
    static float cameraRotationY;
};

#endif
