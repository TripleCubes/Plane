#ifndef SETTINGS_H
#define SETTINGS_H

class Settings {
    friend class Controls;
    
public:
    static bool isFreeCam() { return freeCam; };
    static bool isWireframeMode() { return wireframeMode; };
    static bool isPerspectiveProjection() { return perspectiveProjection; };

private:
    static bool freeCam;
    static bool wireframeMode;
    static bool perspectiveProjection;
};

#endif
