#include <hitbox.h>

void Hitbox::update(double mod){

    move(mod);
    duration -= mod;
    Entity::update(mod);
    alive = alive && duration >= 0;
}

void Hitbox::move(double mod){

    if(_following == NULL){

        pos.fx += (orizontalSpeed * mod);
        pos.fy += (verticalSpeed * mod);
    }else{

        followDistanceX += (orizontalSpeed * mod);
        followDistanceY += (verticalSpeed * mod);

        pos.fx = _following->pos.fx + followDistanceX;
        pos.fy = _following->pos.fy + followDistanceY;
    }
}

void Hitbox::collided(Entity* _e){
    alive =  alive && ((_e->team == 2) || (_e->team == -2) || (_e->team > 0 && team > 0) || (_e->team <0 && team <0));
}

Hitbox* Hitbox::follow(Entity* _e, double distanceX, double distanceY){
    _following = _e;
    followDistanceX = distanceX;
    followDistanceY = distanceY;
    return this;
}