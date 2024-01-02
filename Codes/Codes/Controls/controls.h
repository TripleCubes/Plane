#ifndef CONTROLS_H
#define CONTROLS_H

class Controls {
public:
    static void update();

private:
    static void updateSettings();
    static void updateCameraDir();
    static void updateMovements();
    static void updatePlaceBreak();
    static void updateChunkPlacing();
    static void updateGameSelection();

    static void updateDebugLogKeys();

    static float cameraRotationX;
    static float cameraRotationY;
};

#endif
