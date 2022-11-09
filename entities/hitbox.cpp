#include <hitbox.h>

void Hitbox::update(double mod){
    move(mod);
    duration -= mod;
    if(duration <= 0){alive = false;}
    Entity::update(mod);
}

void Hitbox::move(double mod){
    if(_following == NULL){
        pos.fx += (orizontalSpeed * mod);
        pos.fy += (verticalSpeed * mod);
    }else{
        pos.fx = _following->pos.fx + followDistanceX;
        pos.fy = _following->pos.fy + followDistanceY;
    }
    
}

void Hitbox::collided(Entity* _e){
    if(_e->team != team && _e->team != 0){
        alive = false;
    }
}

Hitbox* Hitbox::follow(Entity* _e, double distanceX, double distanceY){
    _following = _e;
    followDistanceX = distanceX;
    followDistanceY = distanceY;
    return this;
}