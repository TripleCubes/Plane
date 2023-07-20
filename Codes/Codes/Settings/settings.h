#ifndef SETTINGS_H
#define SETTINGS_H

class Settings {
    friend class Controls;
    
public:
    static bool isFreeCam();
    static bool isWireframeMode();

private:
    static bool freeCam;
    static bool wireframeMode;
};

#endif
