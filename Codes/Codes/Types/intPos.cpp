#include <Codes/Types/intPos.h>

#include <Codes/Types/vec3.h>
#include <Codes/Globals/globalConsts.h>
#include <cmath>
#include <functional>

int mod(int a, int b) {
    return a % b >= 0 ? a % b : (a % b) + b;
}

IntPos::IntPos(int x, int y, int z): x(x), y(y), z(z) {}
IntPos::IntPos(Vec3 vec): x(floor(vec.x)), y(floor(vec.y)), z(floor(vec.z)) {}
IntPos::IntPos() {}

bool IntPos::operator == (IntPos pos) const {
    return x==pos.x && y==pos.y && z==pos.z;
}

bool IntPos::operator != (IntPos pos) const {
    return x!=pos.x || y!=pos.y || z!=pos.z;
}

IntPos IntPos::operator + (IntPos pos) const {
    return IntPos(x+pos.x, y+pos.y, z+pos.z);
}

IntPos IntPos::operator - (IntPos pos) const {
    return IntPos(x-pos.x, y-pos.y, z-pos.z);
}

IntPos IntPos::operator * (int num) const {
    return IntPos(x*num, y*num, z*num);
}

IntPos IntPos::operator / (int num) const {
    return IntPos(x/num, y/num, z/num);
}

IntPos IntPos::operator % (int num) const {
    return IntPos(mod(x, num), mod(y, num), mod(z, num));
}

IntPos IntPos::getChunkPos() const {
    return IntPos((int)floor((float)x / CHUNK_WIDTH), (int)floor((float)y / CHUNK_WIDTH), (int)floor((float)z / CHUNK_WIDTH));
}

IntPos IntPos::getBlockPosInChunk() const {
    return *this % CHUNK_WIDTH;
}

int IntPos::getChunkPos(int num) {
    return (int)floor((float)num / CHUNK_WIDTH);
}



std::size_t IntPosHash::operator () (const IntPos &pos) const {
    std::size_t hash1 = std::hash<int>{}(pos.x);
    std::size_t hash2 = std::hash<int>{}(pos.y);
    std::size_t hash3 = std::hash<int>{}(pos.z);
    return (hash1 ^ (hash2 << 1)) ^ (hash3 << 1);
}
