#ifndef SETTINGS_H
#define SETTINGS_H

class Settings {
    friend class Controls;
    
public:
    static bool isFreeCam();
    static bool isWireframeMode();
    static bool isPerspectiveProjection();

private:
    static bool freeCam;
    static bool wireframeMode;
    static bool perspectiveProjection;
};

#endif
