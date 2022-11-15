#include <slash.h>
#include <game.h>

extern Game game;

Slash* Slash::concat(Hitbox* _h){
    _next = _h;

    return this;
}

void Slash::update(double mod){
    Hitbox::update(mod);

    if(!alive && (_next != NULL)){
            game.addEntity(_next);
    }
}

void Slash::collided(Entity* _e){
    Hitbox::collided(_e);

    if(!alive){
        delete(_next);
    }
}