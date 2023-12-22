#include <Codes/Entities/entity.h>

#include <Codes/Chunks/chunkLoader.h>
#include <Codes/Types/intPos.h>
#include <Codes/Time/time.h>
#include <cmath>

#include <Codes/Debug/print.h>
#include <Codes/Debug/debug3d.h>
#include <Codes/Debug/debugUI.h>

const int TOP = 0;
const int BOTTOM = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int FORWARD = 4;
const int BACKWARD = 5;

Entity::Entity() {
    pos = Vec3(6, 20, 8);
    lookDir = Vec3(0, 0, 1);
}

void Entity::update() {
    fallAndJump();

    Vec3 collided;
    collided.y = move(totalMoveVec.y, MoveAxis::Y);
    collided.x = move(totalMoveVec.x, MoveAxis::X);
    collided.z = move(totalMoveVec.z, MoveAxis::Z);

    if (collided.y < 0) {
        status_isOnGround = true;
    } else {
        status_isOnGround = false;
    }

    totalMoveVec = Vec3(0, 0, 0);

    DRAWTEXT(pos + Vec3(0, 3, 0), "This is a test", Color(1, 1, 1, 1), true);
    DRAWUITEXT(pos + Vec3(0, 5, 0), "This is a test", Color(1, 1, 1, 1), true);
}

void Entity::move(Vec3 moveVec) {
    totalMoveVec += moveVec;
}

float Entity::move(float moveAmount, MoveAxis moveAxis) {
    if (moveAmount == 0) {
        return 0;
    }

    int dir = 0;
    switch (moveAxis) {
    case MoveAxis::X:
        if (moveAmount < 0) { dir = LEFT; }
        else { dir = RIGHT; }
        break;

    case MoveAxis::Y:
        if (moveAmount > 0) { dir = TOP; }
        else { dir = BOTTOM; }
        break;

    case MoveAxis::Z:
        if (moveAmount > 0) { dir = FORWARD; }
        else { dir = BACKWARD; }
        break;
    
    default:
        break;
    }

    Vec3 moveVec;
    switch (dir) {
    case TOP:
        moveVec.y = moveAmount;
        break;

    case BOTTOM:
        moveVec.y = moveAmount;
        break;

    case LEFT:
        moveVec.x = moveAmount;
        break;

    case RIGHT:
        moveVec.x = moveAmount;
        break;

    case FORWARD:
        moveVec.z = moveAmount;
        break;

    case BACKWARD:
        moveVec.z = moveAmount;
        break;
    
    default:
        break;
    }

    for (Vec3 physicPoint: physicPointList[dir]) {
        Vec3 nextPhysicPoint = physicPoint + pos + moveVec;
        if (ChunkLoader::chunkLoadCheck_isSolidBlock(IntPos(nextPhysicPoint))) {
            snapToGrid(dir);
            if (dir == TOP || dir == RIGHT || dir == FORWARD) { return 1; }
            return -1;
        }
    }

    pos += moveVec;
    return 0;
}

void Entity::createPhysicPoints(int dir) {
    float startX = -size.x/2 + offset.x;
    float endX = size.x/2 + offset.x;
    float startY = -size.y/2 + offset.y;
    float endY = size.y/2 + offset.y;
    float startZ = -size.z/2 + offset.z;
    float endZ = size.z/2 + offset.z;

    switch (dir) {
    case TOP:
        startY = endY;
        break;

    case BOTTOM:
        endY = startY;
        break;

    case LEFT:
        endX = startX;
        break;

    case RIGHT:
        startX = endX;
        break;

    case FORWARD:
        startZ = endZ;
        break;

    case BACKWARD:
        endZ = startZ;
        break;
    
    default:
        break;
    }

    // CAN BE OPTIMIZED ?
    for (float x = startX; x <= endX;) {
        for (float y = startY; y <= endY;) {
            for (float z = startZ; z <= endZ;) {
                physicPointList[dir].push_back(Vec3(x, y, z));
                if (z < endZ && z + 1 > endZ) { z = endZ; }
                else { z += 1; }
            }
            if (y < endY && y + 1 > endY) { y = endY; }
            else { y += 1; }
        }
        if (x < endX && x + 1 > endX) { x = endX; }
        else { x += 1; }
    }
}

void Entity::snapToGrid(int dir) {
    switch (dir)
    {
    case TOP: {
        Vec3 diff;
        diff.y = size.y / 2 + offset.y;

        Vec3 snapPoint = pos + diff;
        snapPoint.y = ceil(snapPoint.y);
        pos = snapPoint - diff;
        pos.y -= 0.001;
        break;
    }
    
    case BOTTOM: {
        Vec3 diff;
        diff.y = - size.y / 2 + offset.y;

        Vec3 snapPoint = pos + diff;
        snapPoint.y = floor(snapPoint.y);
        pos = snapPoint - diff;
        pos.y += 0.001;
        break;
    }

    case LEFT: {
        Vec3 diff;
        diff.x = - size.x / 2 + offset.x;

        Vec3 snapPoint = pos + diff;
        snapPoint.x = floor(snapPoint.x);
        pos = snapPoint - diff;
        pos.x += 0.001;
        break;
    }

    case RIGHT: {
        Vec3 diff;
        diff.x = size.x / 2 + offset.x;

        Vec3 snapPoint = pos + diff;
        snapPoint.x = ceil(snapPoint.x);
        pos = snapPoint - diff;
        pos.x -= 0.001;
        break;
    }

    case FORWARD: {
        Vec3 diff;
        diff.z = size.z / 2 + offset.z;

        Vec3 snapPoint = pos + diff;
        snapPoint.z = ceil(snapPoint.z);
        pos = snapPoint - diff;
        pos.z -= 0.001;
        break;
    }
    
    case BACKWARD: {
        Vec3 diff;
        diff.z = - size.z / 2 + offset.z;

        Vec3 snapPoint = pos + diff;
        snapPoint.z = floor(snapPoint.z);
        pos = snapPoint - diff;
        pos.z += 0.001;
        break;
    }
    
    default:
        break;
    }
}

void Entity::jump() {
    jumpRequested = true;
}

bool Entity::isOnGround() {
    return status_isOnGround;
}

void Entity::fallAndJump() {
    const float JUMP_GRAVITY = 10;
    const float FALL_ADD_GRAVITY = -30;

    if (jumpRequested && status_isOnGround) {
        gravity = JUMP_GRAVITY;
        return;
    }

    totalMoveVec.y += Time::getDeltaTime() * gravity;

    if (status_isOnGround) {
        gravity = 0;
    }

    gravity += Time::getDeltaTime() * FALL_ADD_GRAVITY;

    jumpRequested = false;
}
