#ifndef CONTROLS_H
#define CONTROLS_H

class Controls {
public:
    static void update();

private:
    static void updateSettings();
    static void updateCameraDir();
    static void updateMovements();
    static void placeBreakBlock();

    static float cameraRotationX;
    static float cameraRotationY;

    static void lockMouse();
    static void unlockMouse();
};

#endif
