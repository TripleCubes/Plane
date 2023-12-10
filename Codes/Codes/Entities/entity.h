#ifndef ENTITY_H
#define ENTITY_H

#include <Codes/Types/vec3.h>
#include <vector>
#include <array>

class Entity {
public:
    Entity();
    void update();
    
    Vec3 getPos() const { return pos; };
    Vec3 getLookDir() const { return lookDir; };

    Vec3 getSize() const { return size; };
    Vec3 getOffset() const { return offset; };

    void move(Vec3 moveVec);
    void jump();
    bool isOnGround();

protected:
    void createPhysicPoints(int dir);

private:
    Vec3 pos;
    Vec3 lookDir = Vec3(0, 0, 1);

    Vec3 size = Vec3(1, 2, 1);
    Vec3 offset = Vec3(0, 1, 0);

    std::array<std::vector<Vec3>, 6> physicPointList;

    Vec3 totalMoveVec;
    
    bool status_isOnGround = false;
    bool jumpRequested = false;
    float gravity = 0;

    enum class MoveAxis {
        X, Y, Z,
    };

    float move(float moveAmount, MoveAxis moveAxis);
    void snapToGrid(int dir);

    void fallAndJump();
};

#endif
