#include <Codes/Chunks/chunkLoader.h>

#include <Codes/Chunks/chunk.h>
#include <Codes/Types/intPos.h>

#include <Codes/Debug/print.h>

std::unordered_map<IntPos, std::unique_ptr<Chunk>, IntPosHash> ChunkLoader::chunks;

void ChunkLoader::init() {
    auto loadPlatform = [](IntPos startPos, IntPos size, BlockType blockType) -> void {
        for (int x = startPos.x; x < startPos.x + size.x; x++) {
        for (int y = startPos.y; y < startPos.y + size.y; y++) {
        for (int z = startPos.z; z < startPos.z + size.z; z++) {
            chunkLoadCheck_setBlock(IntPos(x, y, z), blockType);
        }
        }
        }
    };

    loadPlatform(IntPos(0, 0, 0), IntPos(16, 1, 16*5), BlockType::YELLOW);
    loadPlatform(IntPos(-16*3, 0, 16), IntPos(16* 3, 1, 16), BlockType::BLUE);
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
