#ifndef BLOCKRAYCAST_H
#define BLOCKRAYCAST_H

#include <Codes/Types/intPos.h>
#include <Codes/Chunks/chunk.h>

class Vec3;

struct BlockRayCastResult {
    bool found = false;
    BlockType selectedType = BlockType::EMPTY;
    IntPos selectedPos;

    bool hasPlacingPos = false;
    IntPos placingPos;
};

class BlockRayCast {
public:
    static BlockRayCastResult cast(Vec3 from, Vec3 dir, float range, bool blockGroundHeight);

private:
};

#endif
