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

    static BlockType getBlock(IntPos blockPos);
    static bool isSolidBlock(IntPos blockPos);
    static bool chunkLoaded(IntPos chunkPos);

private:
    static std::unordered_map<IntPos, std::unique_ptr<Chunk>, IntPosHash> chunks;
    
    static void loadChunk(IntPos chunkPos);
    static void setBlock(IntPos blockPos, BlockType blockType);
    static void checkLoadSideChunks(IntPos chunkPos);
    static void requestUpdateSideChunkMeshes(IntPos chunkPos);
    static void updateChunkMesh(IntPos chunkPos, std::unique_ptr<Chunk> &chunkPtr);
};

#endif
