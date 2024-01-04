#include <Codes/PathFind/aStar.h>

#include <Codes/Chunks/columnList.h>
#include <Codes/Chunks/chunkLoader.h>
#include <Codes/Types/intPos.h>
#include <Codes/Types/vec3.h>
#include <cmath>

#include <Codes/Debug/print.h>
#include <Codes/Debug/debug3d.h>

std::array<AStar::TileInformation, CHECK_ARRAY_SIZE> AStar::tileInformationList;
std::array<int, CHECK_ARRAY_SIZE> AStar::tileMarkingList = {};
int AStar::checkingMark = 1;
int AStar::checkedMark = 2;
std::array<IntPos, 24> AStar::dirList = {
    IntPos(-1,  0, -1), IntPos(-1,  0,  0), IntPos(-1,  0,  1),
    IntPos( 0,  0, -1),                     IntPos( 0,  0,  1),
    IntPos( 1,  0, -1), IntPos( 1,  0,  0), IntPos( 1,  0,  1),

    IntPos(-1, -1, -1), IntPos(-1, -1,  0), IntPos(-1, -1,  1),
    IntPos( 0, -1, -1),                     IntPos( 0, -1,  1),
    IntPos( 1, -1, -1), IntPos( 1, -1,  0), IntPos( 1, -1,  1),

    IntPos(-1,  1, -1), IntPos(-1,  1,  0), IntPos(-1,  1,  1),
    IntPos( 0,  1, -1),                     IntPos( 0,  1,  1),
    IntPos( 1,  1, -1), IntPos( 1,  1,  0), IntPos( 1,  1,  1),
};
std::array<int, 24> AStar::dirDistanceList = {
    141, 100, 141,
    100,      100,
    141, 100, 141,

    173, 141, 173,
    141,      141,
    173, 141, 173,

    173, 141, 173,
    141,      141,
    173, 141, 173,
};
int AStar::markIndex = 0;

AStarResult AStar::getPathBlock(IntPos startPos, IntPos endPos) {
    auto canMoveToBlock = [](IntPos world_from, IntPos dir) -> bool {
        IntPos world_to = world_from + dir;

        if (ChunkLoader::chunkLoadCheck_isSolidBlock(world_to)) {
            return false;
        }

        if (!ChunkLoader::chunkLoadCheck_isSolidBlock(world_to + IntPos(0, -1, 0))) {
            return false;
        }

        if (ChunkLoader::chunkLoadCheck_isSolidBlock(world_to + IntPos(0, 1, 0))) {
            return false;
        }

        if (dir.x != 0 && dir.z != 0) {
            IntPos checkDir = dir;
            checkDir.x = 0;
            if (ChunkLoader::chunkLoadCheck_isSolidBlock(world_from + checkDir)) {
                return false;
            }

            checkDir = dir;
            checkDir.z = 0;
            if (ChunkLoader::chunkLoadCheck_isSolidBlock(world_from + checkDir)) {
                return false;
            }

            checkDir = dir + IntPos(0, 1, 0);
            checkDir.x = 0;
            if (ChunkLoader::chunkLoadCheck_isSolidBlock(world_from + checkDir)) {
                return false;
            }

            checkDir = dir + IntPos(0, 1, 0);
            checkDir.z = 0;
            if (ChunkLoader::chunkLoadCheck_isSolidBlock(world_from + checkDir)) {
                return false;
            }
        }

        return true;
    };

    return getPath(startPos, endPos, canMoveToBlock);
}

AStarResult AStar::getPathChunk(IntPos startPos, IntPos endPos) {
    auto canMoveToBlock = [](IntPos world_from, IntPos dir) -> bool {
        if (dir.y != 0) {
            return false;
        }

        if (dir.x != 0 && dir.z != 0) {
            return false;
        }

        IntPos world_to = world_from + dir;
        if (!ColumnList::has(world_to.x, world_to.z)) {
            return false;
        }

        return true;
    };

    return getPath(startPos, endPos, canMoveToBlock);
}

AStarResult AStar::getPath(IntPos world_startPos, IntPos world_endPos, 
                            bool (*canMoveTo)(IntPos world_from, IntPos dir)) {
    // TO DO: Reset the tileMarkingList
    checkingMark += 2;
    checkedMark += 2;

    std::vector<IntPos> addedWorldPosList;

    if (std::abs(world_endPos.x - world_startPos.x) > CHECK_ARRAY_SIZE_X/2 
    || std::abs(world_endPos.y - world_startPos.y) > CHECK_ARRAY_SIZE_Y/2
    || std::abs(world_endPos.z - world_startPos.z) > CHECK_ARRAY_SIZE_Z/2) {
        AStarResult result;
        result.foundResult = AStarFoundResult::OUT_OF_CHECK_ARRAY_SIZE;
        return result;
    }

    IntPos end_checkArr = worldPosTocheckArrayPos(world_startPos, world_endPos);
    int end_index = posToIndex(end_checkArr);

    int num_checked = 0;
    IntPos at_world = world_startPos;
    IntPos at_checkArr = worldPosTocheckArrayPos(world_startPos, at_world);
    int    at_index = posToIndex(at_checkArr);
    markPosAsChecked(at_index);
    TileInformation at_tileInformation = getTileInformationRef(at_index);

    int start_index = at_index;

    while (true) {
    for (std::size_t i = 0; i < dirList.size(); i++) {
        IntPos dir = dirList[i];
        IntPos comp_world = at_world + dir;
        IntPos comp_checkArr = worldPosTocheckArrayPos(world_startPos, comp_world);
        int    comp_index = posToIndex(comp_checkArr);

        if (!(canMoveTo(at_world, dir) 
        && comp_index >= 0 && comp_index < CHECK_ARRAY_SIZE 
        && !checked(comp_index))) {
            continue;
        }

        TileInformation &comp_tileInformation = getTileInformationRef(comp_index);
        int distanceFromStart = dirDistanceList[i] + at_tileInformation.distanceFromStart;
        if (checking(comp_index)) {
            if (distanceFromStart < comp_tileInformation.distanceFromStart) {
                comp_tileInformation.beforeTileIndex = at_index;
                comp_tileInformation.distanceFromStart = distanceFromStart;
                comp_tileInformation.distanceFromEnd = (std::abs(comp_world.x - world_endPos.x) 
                                                        + std::abs(comp_world.y - world_endPos.y)
                                                        + std::abs(comp_world.z - world_endPos.z)) * 100;
            }
        } else {
            comp_tileInformation.beforeTileIndex = at_index;
            comp_tileInformation.distanceFromStart = distanceFromStart;
            comp_tileInformation.distanceFromEnd = (std::abs(comp_world.x - world_endPos.x) 
                                                    + std::abs(comp_world.y - world_endPos.y)
                                                    + std::abs(comp_world.z - world_endPos.z)) * 100;
            markPosAsChecking(comp_index);
            addedWorldPosList.push_back(comp_world);
        }
    }
    num_checked++;
    if (num_checked >= TILE_CHECKED_CAP) {
        AStarResult result;
        result.foundResult = AStarFoundResult::OUT_OF_TILE_CHECKED_CAP;
        return result;
    }
    if (checked(end_index)) {
        AStarResult result;
        result.foundResult = AStarFoundResult::FOUND;
        // CAN BE OPTIMIZED: Put the path or the AStarResult in a pointer
        int index = end_index;
        while (index != start_index) {
            result.pathReversed.push_back(indexToWorldPos(world_startPos, index));
            TileInformation tileInformation = getTileInformationRef(index);
            index = tileInformation.beforeTileIndex;
        }
        result.pathReversed.push_back(indexToWorldPos(world_startPos, start_index));
        return result;
    }

    at_world = getSmallestTotalNumWorldPos(addedWorldPosList, world_startPos);
    at_checkArr = worldPosTocheckArrayPos(world_startPos, at_world);
    at_index = posToIndex(at_checkArr);
    markPosAsChecked(at_index);
    at_tileInformation = getTileInformationRef(at_index);
    }

    return AStarResult();
}

IntPos AStar::worldPosTocheckArrayPos(IntPos world_startPos, IntPos world_pos) {
    return world_pos - world_startPos + Vec3(CHECK_ARRAY_SIZE_X/2, CHECK_ARRAY_SIZE_Y/2, CHECK_ARRAY_SIZE_Z/2);
}

int AStar::posToIndex(IntPos pos) {
    return pos.y*CHECK_ARRAY_SIZE_X*CHECK_ARRAY_SIZE_Z + pos.x*CHECK_ARRAY_SIZE_Z + pos.z;
}

IntPos AStar::indexToWorldPos(IntPos world_startPos, int index) {
    IntPos checkArrPos;
    checkArrPos.y = index / (CHECK_ARRAY_SIZE_X*CHECK_ARRAY_SIZE_Z);
    index = index % (CHECK_ARRAY_SIZE_X*CHECK_ARRAY_SIZE_Z);
    checkArrPos.x = index / CHECK_ARRAY_SIZE_Z;
    index = index % CHECK_ARRAY_SIZE_Z;
    checkArrPos.z = index;
    IntPos worldPos = checkArrPos - Vec3(CHECK_ARRAY_SIZE_X/2, CHECK_ARRAY_SIZE_Y/2, CHECK_ARRAY_SIZE_Z/2) + world_startPos;
    return worldPos;
}

void AStar::markPosAsChecking(int index) {
    tileMarkingList[index] = checkingMark;
}

void AStar::markPosAsChecked(int index) {
    tileMarkingList[index] = checkedMark;
}

bool AStar::checking(int index) {
    return tileMarkingList[index] == checkingMark;
}

bool AStar::checked(int index) {
    return tileMarkingList[index] == checkedMark;
}

AStar::TileInformation &AStar::getTileInformationRef(int index) {
    return tileInformationList[index];
}

IntPos AStar::getSmallestTotalNumWorldPos(const std::vector<IntPos> &addedWorldPosList, IntPos world_startPos) {
    int smallestTotalNum = 9999999;
    IntPos choosenPos;

    for (IntPos pos_world: addedWorldPosList) {
        IntPos pos_checkArr = worldPosTocheckArrayPos(world_startPos, pos_world);
        int index = posToIndex(pos_checkArr);
        if (checked(index)) {
            continue;
        }

        TileInformation tileInfortmation = getTileInformationRef(index);
        int totalNum = tileInfortmation.distanceFromStart + tileInfortmation.distanceFromEnd;
        if (totalNum < smallestTotalNum) {
            smallestTotalNum = totalNum;
            choosenPos = pos_world;
        } 
    }

    return choosenPos;
}
