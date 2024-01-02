#include <Codes/Chunks/chunkLoader.h>

#include <Codes/Chunks/chunk.h>
#include <Codes/Chunks/terrain.h>
#include <Codes/Types/intPos.h>

#include <Codes/Debug/print.h>

std::unordered_map<IntPos, std::unique_ptr<Chunk>, IntPosHash> ChunkLoader::chunks;

void ChunkLoader::init() {
    loadChunkTerrain(IntPos(0, 0, 0));    
    loadChunkTerrain(IntPos(0, 0, 1));    
    loadChunkTerrain(IntPos(1, 0, 0));    
    loadChunkTerrain(IntPos(1, 0, 1));
    requestUpdateAllChunkMeshes();
}

void ChunkLoader::update() {
    for (auto &chunk: chunks) {
        if (!chunk.second->isMeshUpdateRequested()) {
            continue;
        }

        updateChunkMesh(chunk.first, chunk.second);
    }
}

const std::unordered_map<IntPos, std::unique_ptr<Chunk>, IntPosHash> &ChunkLoader::getChunkList() {
    return chunks;
}

void ChunkLoader::chunkLoadCheck_setBlock(IntPos blockPos, BlockType blockType) {
    IntPos chunkPos = blockPos.getChunkPos();
    if (!chunkLoaded(chunkPos)) {
        loadChunk(chunkPos);
    }

    checkLoadSideChunks(chunkPos);
    chunks.at(chunkPos)->setBlock(blockPos.getBlockPosInChunk(), blockType);
}

void ChunkLoader::chunkLoadCheck_setBlockAndUpdate(IntPos blockPos, BlockType blockType) {
    IntPos chunkPos = blockPos.getChunkPos();
    if (!chunkLoaded(chunkPos)) {
        loadChunk(chunkPos);
    }

    checkLoadSideChunks(chunkPos);
    auto &chunkPtr = chunks.at(chunkPos);
    chunkPtr->setBlock(blockPos.getBlockPosInChunk(), blockType);
    chunkPtr->requestMeshUpdate();
}

BlockType ChunkLoader::chunkLoadCheck_getBlock(IntPos blockPos) {
    IntPos chunkPos = blockPos.getChunkPos();
    if (chunkLoaded(chunkPos)) {
        return chunks.at(chunkPos)->getBlock(blockPos.getBlockPosInChunk());
    }
    return BlockType::EMPTY;
}

bool ChunkLoader::chunkLoadCheck_isSolidBlock(IntPos blockPos) {
    return chunkLoadCheck_getBlock(blockPos) != BlockType::EMPTY;
}

void ChunkLoader::loadChunk(IntPos chunkPos) {
    std::unique_ptr<Chunk> chunkPtr = std::make_unique<Chunk>();
    chunks.insert(std::make_pair(chunkPos, std::move(chunkPtr)));
}

bool ChunkLoader::chunkLoaded(IntPos chunkPos) {
    return chunks.find(chunkPos) != chunks.end();
}

void ChunkLoader::checkLoadSideChunks(IntPos chunkPos) {
    std::array<IntPos, 6> dirs = {
        IntPos( 0,  1,  0), // TOP
        IntPos( 0, -1,  0), // BOTTOM
        IntPos(-1,  0,  0), // LEFT
        IntPos( 1,  0,  0), // RIGHT
        IntPos( 0,  0,  1), // FORWARD
        IntPos( 0,  0, -1), // BACKWARD
    };
    for (IntPos dir: dirs) {
        IntPos sideChunkPos = chunkPos + dir;
        if (!chunkLoaded(sideChunkPos)) {
            loadChunk(sideChunkPos);
        }
    }
}

void ChunkLoader::loadChunkTerrain(IntPos chunkPos) {
    if (!chunkLoaded(chunkPos)) {
        loadChunk(chunkPos);
    }

    auto &chunkPtr = chunks.at(chunkPos);
    Terrain::load(chunkPos, chunkPtr);
    checkLoadSideChunks(chunkPos);
}

void ChunkLoader::loadChunkTerrainAndMesh(IntPos chunkPos) {
    if (!chunkLoaded(chunkPos)) {
        loadChunk(chunkPos);
    }

    auto &chunkPtr = chunks.at(chunkPos);
    Terrain::load(chunkPos, chunkPtr);
    checkLoadSideChunks(chunkPos);
    chunkPtr->requestMeshUpdate();
}

void ChunkLoader::requestUpdateAllChunkMeshes() {
    for (auto &chunk: chunks) {
        chunk.second->requestMeshUpdate();
    }
}

void ChunkLoader::requestUpdateSideChunkMeshes(IntPos chunkPos) {
    // CAN BE OPTIMIZED: Only update mesh of chunk next to the placed block
    std::array<IntPos, 6> dirs = {
        IntPos( 0,  1,  0), // TOP
        IntPos( 0, -1,  0), // BOTTOM
        IntPos(-1,  0,  0), // LEFT
        IntPos( 1,  0,  0), // RIGHT
        IntPos( 0,  0,  1), // FORWARD
        IntPos( 0,  0, -1), // BACKWARD
    };
    for (IntPos dir: dirs) {
        IntPos sideChunkPos = chunkPos + dir;
        if (chunkLoaded(sideChunkPos)) {
            chunks.at(sideChunkPos)->requestMeshUpdate();
        }
    }
}

void ChunkLoader::updateChunkMesh(IntPos chunkPos, std::unique_ptr<Chunk> &chunkPtr) {
    if (
        !chunkLoaded(chunkPos + IntPos( 0,  1,  0)) ||  // TOP
        !chunkLoaded(chunkPos + IntPos( 0, -1,  0)) ||  // BOTTOM
        !chunkLoaded(chunkPos + IntPos(-1,  0,  0)) ||  // LEFT
        !chunkLoaded(chunkPos + IntPos( 1,  0,  0)) ||  // RIGHT
        !chunkLoaded(chunkPos + IntPos( 0,  0,  1)) ||  // FORWARD
        !chunkLoaded(chunkPos + IntPos( 0,  0, -1))     // BACKWARD
    ) {
        return;
    }

    std::array<Chunk*, 6> sideChunks = {
        chunks.at(chunkPos + IntPos( 0,  1,  0)).get(), // TOP
        chunks.at(chunkPos + IntPos( 0, -1,  0)).get(), // BOTTOM
        chunks.at(chunkPos + IntPos(-1,  0,  0)).get(), // LEFT
        chunks.at(chunkPos + IntPos( 1,  0,  0)).get(), // RIGHT
        chunks.at(chunkPos + IntPos( 0,  0,  1)).get(), // FORWARD
        chunks.at(chunkPos + IntPos( 0,  0, -1)).get(), // BACKWARD
    };
    chunkPtr->updateMesh(sideChunks);
}
