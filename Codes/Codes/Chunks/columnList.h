#ifndef COLUMNLIST_H
#define COLUMNLIST_H

class IntPos2d;

namespace ColumnList {
    void add(IntPos2d chunkPos);
    void remove(IntPos2d chunkPos);
    bool has(IntPos2d chunkPos);
};

#endif
