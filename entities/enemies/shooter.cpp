#include <game.h>
#include <shooter.h>
#include <math.h>
#include <SDL.h>
#include <hitbox.h>

extern Game game;

void Shooter::update(double mod){
    move(mod);

    if(shootCd >=0) shootCd -= mod;

    SDL_Rect aiming = lastPlayerPos;

    aiming.x -= camera.modX;
    aiming.y -= camera.modY;

    Entity::update(mod);

    alive = (hp > 0);
}

void Shooter::switchMode(EntityList* _head){
    if(_head == NULL){ 
        state = 's';
        return;
    }

    switchMode(_head->_next);

    if(_head->_e->team == 1){

        if(canSee(_head->_e, game._ELHead)){

            lastPlayerPos.x = _head->_e->pos.fx;
            lastPlayerPos.y = _head->_e->pos.fy;

            state = 'a';
        }
    }
}

void Shooter::move(double mod){

    switchMode(game._ELHead);

    switch(state){
        case 'a': //attack
            moveAwayAndShoot();
            break;
        case 's': //search
            search();
            break;
        default: //idle
            idle();
            break;
    }

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

bool Shooter::canSee(Entity* _e, EntityList* _el){
    if(_el == NULL) return true;

    if(_el->_e->team == 0){

        bool result = ((pos.fx <= _el->_e->pos.fx) && (_e->pos.fx <= _el->_e->pos.fx)) || 
                        (((pos.fy+pos.fh) >= (_el->_e->pos.fy+_el->_e->pos.fh)) && ((_e->pos.fy+_e->pos.fh) >= (_el->_e->pos.fy+_el->_e->pos.fh))) ||
                        (((pos.fx+pos.fw) >= (_el->_e->pos.fx+_el->_e->pos.fw)) && ((_e->pos.fx+_e->pos.fw) >= (_el->_e->pos.fx+_el->_e->pos.fw))) ||
                        ((pos.fy <= _el->_e->pos.fy) && (_e->pos.fy <= _el->_e->pos.fy));

        if(!result){return false;}
    }

    return canSee(_e,_el->_next);
}

void Shooter::idle(){

    speedX = 0;
    speedY = 0;
}

void Shooter::search(){
    if(lastPlayerPos.x <0 || lastPlayerPos.y< 0){
        state = 'i';
    }else{
        
        double angle = atan2(lastPlayerPos.y -pos.fy, lastPlayerPos.x -pos.fx);

        speedX = 15 *cos(angle);

        speedY = 15 *sin(angle);
    }
}

void Shooter::moveAwayAndShoot(){
    double dist = sqrt(((lastPlayerPos.x - pos.fx) * (lastPlayerPos.x - pos.fx)) + ((lastPlayerPos.y - pos.fy) * (lastPlayerPos.y - pos.fy)));

    double angle = atan2(lastPlayerPos.y -pos.fy, lastPlayerPos.x -pos.fx);

    speedX = ((dist < safe) ? -30 : 20) *cos(angle);

    speedY = ((dist < safe) ? -30 : 20) *sin(angle);

    if(dist > safe && shootCd <= 0){
        game.addEntity(new Hitbox(_renderer,pos.fx,pos.fy,30,30,-2,20*(cos(angle)),20*(sin(angle)),30,1));
        shootCd = 10;
    }
}