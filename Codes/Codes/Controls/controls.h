#ifndef CONTROLS_H
#define CONTROLS_H

#include <Codes/Types/intPos.h> // TEST
#include <Codes/PathFind/aStar.h> // TEST

class Controls {
public:
    static void update();

private:
    static void updateSettings();
    static void updateCameraDir();
    static void updateMovements();
    static void updateGameSelection();
    static void updateTestEntityPos(); // TEST

    static void updateDebugLogKeys();
    static IntPos startPathFindPos;
    static AStarResult savedAStarResult;

    static float cameraRotationX;
    static float cameraRotationY;
};

#endif
