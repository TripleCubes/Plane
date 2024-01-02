#include <Codes/Chunks/terrain.h>

#include <Codes/Chunks/chunk.h>
#include <Codes/Types/intPos.h>
#include <Codes/Globals/globalConsts.h>
#include <vector>

#include <Codes/Debug/print.h>

FastNoise::SmartNode<FastNoise::OpenSimplex2S> Terrain::fnSimplex;
FastNoise::SmartNode<FastNoise::FractalFBm> Terrain::fnFractal;

void Terrain::init() {
    fnSimplex = FastNoise::New<FastNoise::OpenSimplex2S>();
    fnFractal = FastNoise::New<FastNoise::FractalFBm>();
    
    fnFractal->SetSource(fnSimplex);
    fnFractal->SetOctaveCount(1);
}

void Terrain::load(IntPos chunkPos, std::unique_ptr<Chunk> &chunkPtr) {
    std::vector<float> terrainHeightList(CHUNK_WIDTH * CHUNK_WIDTH);
    fnFractal->GenUniformGrid2D(terrainHeightList.data(), chunkPos.x * CHUNK_WIDTH, chunkPos.z * CHUNK_WIDTH,
                                    CHUNK_WIDTH, CHUNK_WIDTH, 0.01f, 100);

    int i = 0;
    for (int z = 0; z < CHUNK_WIDTH; z++) {
    for (int x = 0; x < CHUNK_WIDTH; x++) {
        int terrainHeight = float((terrainHeightList[i] + 1) / 2) * CHUNK_WIDTH;
        i++;
        for (int y = 0; y < CHUNK_WIDTH; y++) {
            if (y < terrainHeight) {
                chunkPtr->setBlock(IntPos(x, y, z), BlockType::WHITE);
            }
        }
    }
    }
}
