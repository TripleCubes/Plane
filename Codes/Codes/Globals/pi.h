#ifndef PI_H
#define PI_H

#include <cmath>

const float PI = std::atan(1)*4;
const float PI_DIV_180 = PI/180;

float radToDeg(float rad);
float degToRad(float deg);

#endif
