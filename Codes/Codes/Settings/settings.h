#ifndef SETTINGS_H
#define SETTINGS_H

class Settings {
    friend class Controls;
    friend class UIControls;
    
public:
    enum class MouseMode {
        CHUNK,
        SELECT,
    };

    static bool isFreeCam() { return freeCam; };
    static bool isWireframeMode() { return wireframeMode; };
    static bool isPerspectiveProjection() { return perspectiveProjection; };
    static MouseMode getMouseMode() { return mouseMode; };

private:
    static bool freeCam;
    static bool wireframeMode;
    static bool perspectiveProjection;
    static MouseMode mouseMode;
};

#endif
