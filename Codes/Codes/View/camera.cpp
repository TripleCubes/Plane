#include <Codes/View/camera.h>

Vec3 Camera::pos(0, 30, 0);
Vec3 Camera::dir(0, 0, -1);

Vec3 Camera::getPos() {
    return pos;
}

Vec3 Camera::getDir() {
    return dir;
}
