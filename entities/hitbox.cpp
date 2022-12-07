#include <teams.h>
#include <hitbox.h>

void Hitbox::update(double mod, EntityList* _h){

    move(mod,_h);
    duration -= mod;
    Entity::update(mod,_h);
    alive = alive && duration >= 0;
}

void Hitbox::move(double mod, EntityList* _h){

    double distX = 0, distY = 0;

    if(_following == NULL){

        distX += (orizontalSpeed * mod);
        distY += (verticalSpeed * mod);
    }else{

        followDistanceX += (orizontalSpeed * mod);
        followDistanceY += (verticalSpeed * mod);

        distX = _following->pos.fx + followDistanceX - pos.fx;
        distY = _following->pos.fy + followDistanceY - pos.fy;
    }

    while(distX != 0 || distY != 0){

        if(distX >= pos.fw){
            pos.fx += pos.fw;
            distX -= pos.fw;
        }else if(distX <= -pos.fw){
            pos.fx -= pos.fw;
            distX += pos.fw;
        }else{
            pos.fx += distX;
            distX = 0;
        }

        if(distY >= pos.fw){
            pos.fy += pos.fw;
            distY -= pos.fw;
        }else if(distY <= -pos.fw){
            pos.fy -= pos.fw;
            distY += pos.fw;
        }else{
            pos.fy += distY;
            distY = 0;
        }

        checkCollisions(_h);
    }
}

void Hitbox::collided(Entity* _e){
    alive =  alive && ((_e->team == TEAM_ENEMY_PRJECTILE) || (_e->team == TEAM_PLAYER_PROJECTILE) || (_e->team >= TEAM_PLAYER && team >= TEAM_PLAYER) || (_e->team <= TEAM_ENEMY && team <= TEAM_ENEMY));
}

Hitbox* Hitbox::follow(Entity* _e, double distanceX, double distanceY){
    _following = _e;
    followDistanceX = distanceX;
    followDistanceY = distanceY;
    return this;
}