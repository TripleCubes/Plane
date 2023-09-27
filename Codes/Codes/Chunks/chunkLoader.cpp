#include <Codes/Chunks/chunkLoader.h>

#include <Codes/Chunks/chunk.h>
#include <Codes/Types/intPos.h>

#include <Codes/Debug/print.h>

std::unordered_map<IntPos, std::unique_ptr<Chunk>, IntPosHash> ChunkLoader::chunks;

std::size_t IntPosHash::operator () (const IntPos &pos) const {
    std::size_t hash1 = std::hash<int>{}(pos.x);
    std::size_t hash2 = std::hash<int>{}(pos.y);
    std::size_t hash3 = std::hash<int>{}(pos.z);
    return (hash1 ^ (hash2 << 1)) ^ (hash3 << 1);
}

void ChunkLoader::init() {
    auto loadPlatform = [](IntPos pos, BlockType blockType) -> void {
        for (int x = 0; x < 16; x++) {
            for (int z = 0; z < 16; z++) {
                IntPos blockPos = pos*CHUNK_WIDTH + IntPos(x, 15, z);
                setBlock(blockPos, blockType);
            }
        }
        chunks.at(pos)->requestMeshUpdate();
    };

    loadPlatform(IntPos(0, 0, 0), BlockType::WHITE);
    loadPlatform(IntPos(0, 0, 1), BlockType::BLUE);
    loadPlatform(IntPos(0, 0, 2), BlockType::RED);
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

void ChunkLoader::setBlock(IntPos blockPos, BlockType blockType) {
    IntPos chunkPos = blockPos.getChunkPos();
    if (!chunkLoaded(chunkPos)) {
        loadChunk(chunkPos);
    }

    checkLoadSideChunks(chunkPos);
    chunks.at(chunkPos)->setBlock(blockPos.getBlockPosInChunk(), blockType);
}

BlockType ChunkLoader::getBlock(IntPos blockPos) {
    IntPos chunkPos = blockPos.getChunkPos();
    if (chunkLoaded(chunkPos)) {
        return chunks.at(chunkPos)->getBlock(blockPos.getBlockPosInChunk());
    }
    return BlockType::EMPTY;
}

bool ChunkLoader::isSolidBlock(IntPos blockPos) {
    return getBlock(blockPos) != BlockType::EMPTY;
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
