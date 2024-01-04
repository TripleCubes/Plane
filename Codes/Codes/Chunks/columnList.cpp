#include <Codes/Chunks/columnList.h>

#include <Codes/Types/intPos.h>
#include <unordered_set>

namespace {
    std::unordered_set<IntPos, IntPosHash> column_list;
}

void ColumnList::add(int chunkX, int chunkZ) {
    column_list.insert(IntPos(chunkX, 0, chunkZ));
}

void ColumnList::remove(int chunkX, int chunkZ) {
    column_list.erase(IntPos(chunkX, 0, chunkZ));
}

bool ColumnList::has(int chunkX, int chunkZ) {
    return column_list.find(IntPos(chunkX, 0, chunkZ)) != column_list.end();
}
