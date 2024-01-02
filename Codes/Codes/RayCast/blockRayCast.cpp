#include <Codes/RayCast/blockRayCast.h>

#include <Codes/Chunks/chunkLoader.h>
#include <Codes/Types/vec3.h>
#include <cmath>

#include <Codes/Debug/print.h>

bool isMin(float num1, float num2, float num3) {
    return num1 <= num2 && num1 <= num3;
}

Vec3 nextCheckingPos(Vec3 checkingPos, Vec3 dir) {
    if (dir == Vec3(0, 0, 0)) {
        LINEINFORMATION();
        PRINTLN("dir cant be Vec3(0, 0, 0)");
        return Vec3(0, 0, 0);
    }

    Vec3 dirSign;
    if (dir.x > 0) {
        dirSign.x = 1;
    } else {
        dirSign.x = -1;
    }

    if (dir.y > 0) {
        dirSign.y = 1;
    } else {
        dirSign.y = -1;
    }

    if (dir.z > 0) {
        dirSign.z = 1;
    } else {
        dirSign.z = -1;
    }

    Vec3 distanceToBlockEdge;
    if (dir.x > 0) {
        distanceToBlockEdge.x = ceil(checkingPos.x) - checkingPos.x + 0.001;
    } else {
        distanceToBlockEdge.x = checkingPos.x - floor(checkingPos.x) + 0.001;
    }

    if (dir.y > 0) {
        distanceToBlockEdge.y = ceil(checkingPos.y) - checkingPos.y + 0.001;
    } else {
        distanceToBlockEdge.y = checkingPos.y - floor(checkingPos.y) + 0.001;
    }

    if (dir.z > 0) {
        distanceToBlockEdge.z = ceil(checkingPos.z) - checkingPos.z + 0.001;
    } else {
        distanceToBlockEdge.z = checkingPos.z - floor(checkingPos.z) + 0.001;
    }

    dir = dir.normalize() * 2;  // this is to make distanceToBlockEdge.x(yz) / abs(dir.x(yz)) always
                                // smaller than 1
    Vec3 distanceDivDir;
    distanceDivDir.x = dir.x!=0 ? distanceToBlockEdge.x/abs(dir.x) : 1; // if distanceDivDir.x == 1
    distanceDivDir.y = dir.y!=0 ? distanceToBlockEdge.y/abs(dir.y) : 1; // then it will always be larger
    distanceDivDir.z = dir.z!=0 ? distanceToBlockEdge.z/abs(dir.z) : 1; // than distanceDivDir of axis that
                                                                        // dir != 0, which make it automatically
                                                                        // fail the test
    if (isMin(distanceDivDir.x, distanceDivDir.y, distanceDivDir.z)) {
        Vec3 nextPos;
        nextPos.x = checkingPos.x + distanceToBlockEdge.x * dirSign.x;
        nextPos.y = checkingPos.y + distanceToBlockEdge.x / abs(dir.x) * abs(dir.y) * dirSign.y; // if distanceDivDir.x is min,
        nextPos.z = checkingPos.z + distanceToBlockEdge.x / abs(dir.x) * abs(dir.z) * dirSign.z; // dir.x wouldnt be 0

        if (floor(checkingPos.y) != floor(nextPos.y)) {
            nextPos.y -= dirSign.y * 0.0015;
        }
        if (floor(checkingPos.z) != floor(nextPos.z)) {
            nextPos.z -= dirSign.z * 0.0015;
        }
        return nextPos;
    }
    if (isMin(distanceDivDir.y, distanceDivDir.x, distanceDivDir.z)) {
        Vec3 nextPos;
        nextPos.y = checkingPos.y + distanceToBlockEdge.y * dirSign.y;
        nextPos.x = checkingPos.x + distanceToBlockEdge.y / abs(dir.y) * abs(dir.x) * dirSign.x;
        nextPos.z = checkingPos.z + distanceToBlockEdge.y / abs(dir.y) * abs(dir.z) * dirSign.z;

        if (floor(checkingPos.x) != floor(nextPos.x)) {
            nextPos.x -= dirSign.x * 0.0015;
        }
        if (floor(checkingPos.z) != floor(nextPos.z)) {
            nextPos.z -= dirSign.z * 0.0015;
        }
        return nextPos;
    }
    // if distanceDivDir.z is min
    Vec3 nextPos;
    nextPos.z = checkingPos.z + distanceToBlockEdge.z * dirSign.z;
    nextPos.x = checkingPos.x + distanceToBlockEdge.z / abs(dir.z) * abs(dir.x) * dirSign.x;
    nextPos.y = checkingPos.y + distanceToBlockEdge.z / abs(dir.z) * abs(dir.y) * dirSign.y;

    if (floor(checkingPos.y) != floor(nextPos.y)) {
            nextPos.y -= dirSign.y * 0.0015;
    }
    if (floor(checkingPos.x) != floor(nextPos.x)) {
        nextPos.x -= dirSign.x * 0.0015;
    }
    return nextPos;
}

// CAN BE OPTIMIZED: Skip chunk checking if chunk is unloaded
BlockRayCastResult BlockRayCast::cast(Vec3 from, Vec3 dir, float range, bool blockGroundHeight) {
    Vec3 checkingPos = from;
    Vec3 previousCheckingPos;
    bool hasPlacingPos = false;
    while (from.distance(checkingPos) < range) {
        IntPos checkingIntPos(checkingPos);
        BlockType blockType = ChunkLoader::chunkLoadCheck_getBlock(checkingIntPos);
        if ((blockGroundHeight && checkingIntPos.y == 0)
        || (blockType != BlockType::EMPTY)) {
            BlockRayCastResult result;
            result.found = true;
            result.selectedType = blockType;
            result.selectedPos = checkingIntPos;
            if (hasPlacingPos) {
                result.hasPlacingPos = true;
                result.placingPos = IntPos(previousCheckingPos);
            }
            return result;
        }
        hasPlacingPos = true;
        previousCheckingPos = checkingPos;
        checkingPos = nextCheckingPos(checkingPos, dir);
    }

    return BlockRayCastResult(); // result.found is false by default
}
