#include <Codes/Types/intPos2d.h>

#include <functional>

std::size_t IntPos2dHash::operator () (const IntPos2d &pos) const {
    std::size_t hash1 = std::hash<int>{}(pos.x);
    std::size_t hash2 = std::hash<int>{}(pos.y);
    return hash1 ^ (hash2 << 1);
}
