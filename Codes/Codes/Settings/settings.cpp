#include <Codes/Settings/settings.h>

bool Settings::freeCam = true;
bool Settings::wireframeMode = false;
bool Settings::perspectiveProjection = true;

bool Settings::isFreeCam() {
    return freeCam;
}

bool Settings::isWireframeMode() {
    return wireframeMode;
}

bool Settings::isPerspectiveProjection() {
    return perspectiveProjection;
}
