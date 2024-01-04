#include <Codes/Chunks/columnList.h>

#include <Codes/Types/intPos2d.h>
#include <unordered_set>

namespace {
    std::unordered_set<IntPos2d, IntPos2dHash> column_list;
}

void ColumnList::add(IntPos2d chunkPos) {
    column_list.insert(chunkPos);
}

void ColumnList::remove(IntPos2d chunkPos) {
    column_list.erase(chunkPos);
}

bool ColumnList::has(IntPos2d chunkPos) {
    return column_list.find(chunkPos) != column_list.end();
}
