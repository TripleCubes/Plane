#ifndef ENTITY_H
#define ENTITY_H

#include <Codes/Types/vec3.h>
#include <vector>
#include <array>

class Entity {
public:
    Vec3 getPos() const { return pos; };
    Vec3 getLookDir() const { return lookDir; };

    Vec3 getSize() const { return size; };
    Vec3 getOffset() const { return offset; };

private:
    Vec3 pos = Vec3(0, 20, 0);
    Vec3 lookDir = Vec3(0, 0, 1);

    Vec3 size = Vec3(1, 2, 1);
    Vec3 offset = Vec3(0, 1, 0);

    std::array<std::vector<Vec3>, 6> physicPointList; 

    enum class MoveAxis {
        X, Y, Z,
    };

    void move(Vec3 moveVec);
    void move(float moveAmount, MoveAxis moveAxis);

    void createPhysicPoints(int dir);
    void snapToGrid(int dir);
};

#endif
