
#include <point.h>
#include <SDL.h>

class Entity{
    Point pos,dim;

    int team;
};

struct EntityList{
    Entity* _e;
    EntityList* _next;
};