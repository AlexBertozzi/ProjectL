#include <game.h>
#include <shooter.h>
#include <math.h>
#include <SDL.h>
#include <hitbox.h>

extern Game game;

void Shooter::update(double mod){
    move(mod);

    if(shootCd >=0) shootCd -= mod;

    Entity::update(mod);

    alive = (hp > 0);
}

void Shooter::moveAwayAndShoot(EntityList* _head){
    if(_head == NULL) return;

    if(_head->_e->team == 1){

        double dist = sqrt(((_head->_e->pos.fx - pos.fx) * (_head->_e->pos.fx - pos.fx)) + ((_head->_e->pos.fy - pos.fy) * (_head->_e->pos.fy - pos.fy)));

        double angle = atan2(_head->_e->pos.y -pos.fy + camera.modY, _head->_e->pos.x -pos.fx + camera.modX);

        speedX = ((dist < safe) ? -(dist/20) : (dist/20)) *cos(angle);

        speedY = ((dist < safe) ? -(dist/20) : (dist/20)) *sin(angle);

        if(dist > safe && shootCd <= 0){
            game.addEntity(new Hitbox(_renderer,pos.fx,pos.fy,30,30,-2,20*(cos(angle)),20*(sin(angle)),30,1));
            shootCd = 10;
        }
    }

    moveAwayAndShoot(_head->_next);
}

void Shooter::move(double mod){

    moveAwayAndShoot(game._ELHead);

    pos.fx += speedX * mod;

    pos.fy += speedY * mod;
}

void Shooter::collided(Entity* _e){

    if(_e->team == 0){

        if((pos.fx+ (2*pos.fw/3)) <= (_e->pos.fx)){

            pos.fx = _e->pos.fx - pos.fw;
        }else if((_e->pos.fx+ _e->pos.fw) <= (pos.fx + (pos.fw/3))){

            pos.fx = _e->pos.fx + _e->pos.fw;            
        }else if(((pos.fy+ (2*pos.fh/3)) <= (_e->pos.fy))){

            pos.fy = _e->pos.fy - pos.fh;
        }else if(((_e->pos.fy+ _e->pos.fh)) <= (pos.fy + (pos.fw/3))){

            pos.fy = _e->pos.fy + _e->pos.fh;
        }
    }

    if(_e->team >0){
        hp -= _e->contactDamage;
    }

}