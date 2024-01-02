#ifndef TERRAIN_H
#define TERRAIN_H

#include <memory>
#include <FastNoise/FastNoise.h>
class Chunk;
class IntPos;

class Terrain {
public:
    static void init();
    static void load(IntPos chunkPos, std::unique_ptr<Chunk> &chunkPtr);

private:
    static FastNoise::SmartNode<FastNoise::OpenSimplex2S> fnSimplex;
    static FastNoise::SmartNode<FastNoise::FractalFBm> fnFractal;
};

#endif
