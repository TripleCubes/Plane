#include <Codes/Globals/pi.h>

float radToDeg(float rad) {
    return rad / PI_DIV_180;
}

float degToRad(float deg) {
    return deg * PI_DIV_180;
}
