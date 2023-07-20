#include <Codes/Settings/settings.h>

bool Settings::freeCam = true;
bool Settings::wireframeMode = false;

bool Settings::isFreeCam() {
    return freeCam;
}

bool Settings::isWireframeMode() {
    return wireframeMode;
}
