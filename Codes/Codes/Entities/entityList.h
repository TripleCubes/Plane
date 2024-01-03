#ifndef ENTITYLIST_H
#define ENTITYLIST_H

#include <vector>
#include <memory>
class Entity;
class Vec3;

class EntityList {
public:
    static void init();
    static void update();
    static void add(Vec3 pos);
    static const std::vector<std::shared_ptr<Entity>> &getList(); 

private:
    static std::vector<std::shared_ptr<Entity>> list;
};

#endif
