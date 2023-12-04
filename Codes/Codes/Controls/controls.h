#ifndef CONTROLS_H
#define CONTROLS_H

class Controls {
public:
    static void update();

private:
    static void updateSettings();
    static void updateCameraDir();
    static void updateMovements();
    static void updateGameSelection();
    static void updateTestEntityPos(); // TEST

    static float cameraRotationX;
    static float cameraRotationY;
};

#endif
