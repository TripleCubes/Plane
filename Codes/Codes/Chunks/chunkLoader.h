#ifndef CHUNKLOADER_H
#define CHUNKLOADER_H

#include <unordered_map>
#include <memory>

class Chunk;
class IntPos;
enum class BlockType;

struct IntPosHash {
    std::size_t operator () (const IntPos &pos) const;
};

class ChunkLoader {
public:
    static void init();
    static void update();
    
    static const std::unordered_map<IntPos, std::unique_ptr<Chunk>, IntPosHash> &getChunkList();

    static void placeBlock(IntPos blockPos, BlockType blockType);
    static void breakBlock(IntPos blockPos);
    static BlockType getBlock(IntPos blockPos);
    static bool isSolidBlock(IntPos blockPos);

private:
    static std::unordered_map<IntPos, std::unique_ptr<Chunk>, IntPosHash> chunks;
    
    static void loadChunk(IntPos chunkPos);
    static bool chunkLoaded(IntPos chunkPos);
    static void requestUpdateSideChunkMeshes(IntPos chunkPos);
    static void updateChunkMesh(IntPos chunkPos, std::unique_ptr<Chunk> &chunkPtr);
};

#endif
