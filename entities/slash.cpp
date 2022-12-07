#include <slash.h>
#include <game.h>

extern Game game;

Slash* Slash::concat(Hitbox* _h){
    _next = _h;

    return this;
}

void Slash::update(double mod, EntityList* _h){
    Hitbox::update(mod,_h);

    if(!alive && (_next != NULL)){
        game.addEntity(_next);
        _next = NULL;
    }
}
