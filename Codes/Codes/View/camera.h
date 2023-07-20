#ifndef CAMERA_H
#define CAMERA_H

#include <Codes/Types/vec3.h>

class Camera {
    friend class Controls;
    
public:
    static Vec3 getPos();
    static Vec3 getDir();

private:
    static Vec3 pos;
    static Vec3 dir;
};

#endif
