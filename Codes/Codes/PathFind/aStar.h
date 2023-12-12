#ifndef ASTAR_H
#define ASTAR_H

class IntPos;
#include <vector>
#include <array>

const int CHECK_ARRAY_SIZE_X = 16*3;
const int CHECK_ARRAY_SIZE_Y = 16*3;
const int CHECK_ARRAY_SIZE_Z = 16*3;
const int CHECK_ARRAY_SIZE = CHECK_ARRAY_SIZE_X*CHECK_ARRAY_SIZE_Y*CHECK_ARRAY_SIZE_Z;

const int TILE_CHECKED_CAP = 1000;

enum class AStarFoundResult {
    FOUND,
    OUT_OF_CHECK_ARRAY_SIZE,
    OUT_OF_TILE_CHECKED_CAP,
    BLOCKED,
};

struct AStarResult {
    AStarFoundResult foundResult = AStarFoundResult::BLOCKED;
    std::vector<IntPos> pathReversed;
};

class AStar {
public:
    static AStarResult getPathBlock(IntPos startPos, IntPos endPos);
    static AStarResult getPathChunk(IntPos startPos, IntPos endPos);

private:
    struct TileInformation {
        int distanceFromStart = 0;
        int distanceFromEnd = 0;
        int beforeTileIndex = 0;
    };
    static std::array<TileInformation, CHECK_ARRAY_SIZE> tileInformationList;
    static std::array<unsigned char, CHECK_ARRAY_SIZE> tileMarkingList;
    static std::array<unsigned char, 2> checkingMarkList;
    static std::array<unsigned char, 2> checkedMarkList;
    static std::array<IntPos, 24> dirList;
    static std::array<int, 24> dirDistanceList;
    static int markIndex;

    static AStarResult getPath(IntPos world_startPos, IntPos world_endPos, 
                                bool (*canMoveTo)(IntPos world_from, IntPos world_to));
    static int getCheckingMark();
    static int getCheckedMark();
    static IntPos worldPosTocheckArrayPos(IntPos world_startPos, IntPos world_pos);
    static int posToIndex(IntPos pos);
    static IntPos indexToWorldPos(IntPos world_startPos, int index);
    static void markPosAsChecking(int index);
    static void markPosAsChecked(int index);
    static bool checking(int index);
    static bool checked(int index);
    static TileInformation &getTileInformationRef(int index);
    static IntPos getSmallestTotalNumWorldPos(const std::vector<IntPos> &addedWorldPosList, IntPos world_startPos);
};

#endif
