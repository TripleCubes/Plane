#ifndef CHUNK_H
#define CHUNK_H

#include <Codes/GraphicTypes/mesh.h>
#include <Codes/Types/intPos.h>
#include <Codes/Globals/globalConsts.h>
#include <array>
#include <vector>

enum class BlockType {
    EMPTY = 0,
    WHITE = 1,
    BLUE = 2,
    RED = 3,
    GREEN = 4,
    YELLOW = 5,
};

class Chunk {    
public:
    static int posToIndex(IntPos pos);
    static IntPos indexToPos(int index);

    Chunk();

    void setBlock_noMeshUpdate(int index, BlockType blockType);

    void placeBlock(IntPos pos, BlockType blockType);
    void breakBlock(IntPos pos);
    BlockType getBlock(IntPos pos) const;
    bool isSolidBlock(IntPos pos) const;

    void updateMesh(const std::array<Chunk*, 6> &sideChunks);
    void requestMeshUpdate();
    bool isMeshUpdateRequested() const;

    void draw() const;

private:
    std::array<BlockType, CHUNK_VOLUME> blocks;
    Mesh mesh;

    bool chunkReady = false;
    bool emptyChunkMesh = false;
    bool meshUpdateRequested = true;

    void createFaceList(std::array<bool, CHUNK_VOLUME*6> &faceList, 
                            const std::array<Chunk*, 6> &sideChunks) const;
    struct Surface {
        int colorIndex;
        int w = 0;
        int h = 0;
        int faceDir = 0;
        IntPos blockPos;
    };
    void createSurfaceList(std::vector<Surface> &surfaceList, 
                            std::array<bool, CHUNK_VOLUME*6> &faceList) const;
    void createVerticies(std::vector<float> &verticies, 
                            std::vector<Surface> &surfaceList) const;
};

#endif
