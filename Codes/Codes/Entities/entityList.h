#ifndef ENTITYLIST_H
#define ENTITYLIST_H

class Entity;
#include <vector>

class EntityList {
public:
    static void init();
    static const std::vector<Entity> &getList(); 

private:
    static std::vector<Entity> list;
};

#endif
