#include <Codes/Entities/entity.h>

#include <Codes/Chunks/chunkLoader.h>
#include <Codes/Types/intPos.h>
#include <cmath>

const int TOP = 0;
const int BOTTOM = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int FORWARD = 4;
const int BACKWARD = 5;

void Entity::move(Vec3 moveVec) {
    move(moveVec.y, MoveAxis::Y);
    move(moveVec.x, MoveAxis::X);
    move(moveVec.z, MoveAxis::Z);
}

void Entity::move(float moveAmount, MoveAxis moveAxis) {
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
        moveVec.y = -moveAmount;
        break;

    case LEFT:
        moveVec.x = -moveAmount;
        break;

    case RIGHT:
        moveVec.x = moveAmount;
        break;

    case FORWARD:
        moveVec.z = moveAmount;
        break;

    case BACKWARD:
        moveVec.z = -moveAmount;
        break;
    
    default:
        break;
    }

    for (Vec3 physicPoint: physicPointList[dir]) {
        Vec3 nextPhysicPoint = physicPoint + pos + moveVec;
        if (ChunkLoader::chunkLoadCheck_isSolidBlock(IntPos(nextPhysicPoint))) {
            snapToGrid(dir);
        }
    }
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
    float x = startX;
    float y = startY;
    float z = startZ;
    do {
        do {
            do {
                physicPointList[dir].push_back(Vec3(x, y, z));
                if (z < endZ && z + 1 > endZ) { z = endZ; }
                else { z += 1; }
            } while (z <= endZ);
            if (y < endY && y + 1 > endY) { y = endY; }
            else { y += 1; }
        } while (y <= endY);
        if (x < endX && x + 1 > endX) { x = endX; }
        else { x += 1; }
    } while (x <= endX);
}

void Entity::snapToGrid(int dir) {
    switch (dir)
    {
    case TOP:
        Vec3 diff;
        diff.y = size.y / 2 + offset.y;

        Vec3 snapPoint = pos + diff;
        snapPoint.y = ceil(snapPoint.y);
        pos = snapPoint - diff;
        break;
    
    case BOTTOM:
        Vec3 diff;
        diff.y = - size.y / 2 + offset.y;

        Vec3 snapPoint = pos + diff;
        snapPoint.y = floor(snapPoint.y);
        pos = snapPoint - diff;
        break;

    case LEFT:
        Vec3 diff;
        diff.x = - size.x / 2 + offset.x;

        Vec3 snapPoint = pos + diff;
        snapPoint.x = floor(snapPoint.x);
        pos = snapPoint - diff;
        break;

    case RIGHT:
        Vec3 diff;
        diff.x = size.x / 2 + offset.x;

        Vec3 snapPoint = pos + diff;
        snapPoint.x = ceil(snapPoint.x);
        pos = snapPoint - diff;
        break;

    case FORWARD:
        Vec3 diff;
        diff.z = size.z / 2 + offset.z;

        Vec3 snapPoint = pos + diff;
        snapPoint.z = ceil(snapPoint.z);
        pos = snapPoint - diff;
        break;
    
    case BACKWARD:
        Vec3 diff;
        diff.z = - size.z / 2 + offset.z;

        Vec3 snapPoint = pos + diff;
        snapPoint.z = floor(snapPoint.z);
        pos = snapPoint - diff;
        break;
    
    default:
        break;
    }
}
