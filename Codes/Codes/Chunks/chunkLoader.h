#ifndef CHUNKLOADER_H
#define CHUNKLOADER_H

#include <unordered_map>
#include <memory>

class Chunk;
class IntPos;
struct IntPosHash;
enum class BlockType;

class ChunkLoader {
public:
    static void init();
    static void update();
    
    static const std::unordered_map<IntPos, std::unique_ptr<Chunk>, IntPosHash> &getChunkList();

    static BlockType chunkLoadCheck_getBlock(IntPos blockPos);
    static void chunkLoadCheck_setBlockAndUpdate(IntPos blockPos, BlockType blockType);
    static bool chunkLoadCheck_isSolidBlock(IntPos blockPos);
    static bool chunkLoaded(IntPos chunkPos);

    static void loadChunkTerrain(int x, int z);
    static void loadChunkTerrainAndMesh(int x, int z);

private:
    static std::unordered_map<IntPos, std::unique_ptr<Chunk>, IntPosHash> chunks;
    
    static void loadChunk(IntPos chunkPos);
    static void chunkLoadCheck_setBlock(IntPos blockPos, BlockType blockType);
    static void checkLoadSideChunks(IntPos chunkPos);
    static void requestUpdateAllChunkMeshes();
    static void requestUpdateSideChunkMeshes(IntPos chunkPos);
    static void updateChunkMesh(IntPos chunkPos, std::unique_ptr<Chunk> &chunkPtr);
};

#endif
