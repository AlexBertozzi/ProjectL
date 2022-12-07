#include <teams.h>
#include <game.h>
#include <shooter.h>
#include <math.h>
#include <SDL.h>
#include <hitbox.h>

extern Game game;

void Shooter::update(double mod, EntityList* _h){
    move(mod,_h);

    if(shootCd >=0) shootCd -= mod;

    SDL_Rect aiming = lastPlayerPos;

    aiming.x -= camera.modX;
    aiming.y -= camera.modY;

    Entity::update(mod,_h);

    alive = (hp > 0);
}

void Shooter::switchMode(EntityList* _head){
    if(_head == NULL){ 
        state = 's';
        return;
    }

    switchMode(_head->_next);

    if(_head->_e->team == TEAM_PLAYER){

        double a = pos.fx - _head->_e->pos.fx;
        double b = pos.fy - _head->_e->pos.fy;

        double dist = sqrt((a*a) + (b*b));
        
        double myAngle = atan2((pos.fx + (pos.fw /2))- (_head->_e->pos.fx + (_head->_e->pos.fw /2)) , (pos.fy + (pos.fh /2))- (_head->_e->pos.fy + (_head->_e->pos.fh /2)));

        if(canSee(dist,myAngle, _head->_e, game._ELHead)){

            lastPlayerPos.x = _head->_e->pos.fx;
            lastPlayerPos.y = _head->_e->pos.fy;

            state = 'a';
        }
    }
}

void Shooter::move(double mod, EntityList* _h){

    double distX = 0, distY = 0;

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

    distX += speedX * mod;

    distY += speedY * mod;

    while(distX != 0 && distY != 0){

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

void Shooter::collided(Entity* _e){

    if(_e->team == TEAM_TERRAIN || _e->team == TEAM_ENEMY){

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

    if(_e->team >= TEAM_PLAYER){
        hp -= _e->contactDamage;
    }

}

bool Shooter::canSee(double dist, double myAngle,Entity* _e, EntityList* _el){
    if(_el == NULL) return true;

    if(_el->_e->team == TEAM_TERRAIN){

        Entity* _t = _el->_e;

        bool result;

        double a = _e->pos.fx - _t->pos.fx;
        double b = _e->pos.fy - _t->pos.fy;

        double dist2 = sqrt((a*a) + (b*b));

        if(dist2 < dist){

            double x,y;

            x = (_t->pos.fx)- (_e->pos.fx + (_e->pos.fw /2));

            y = (_t->pos.fy)- (_e->pos.fy + (_e->pos.fh /2));

            double hisAngle1 = atan2( x, y);

            x = (_t->pos.fx)- (_e->pos.fx + (_e->pos.fw /2));

            y = (_t->pos.fy + (_t->pos.fh))- (_e->pos.fy + (_e->pos.fh /2));

            double hisAngle3 = atan2(x , y);

            x = (_t->pos.fx + (_t->pos.fw))- (_e->pos.fx + (_e->pos.fw /2));

            y = (_t->pos.fy)- (_e->pos.fy + (_e->pos.fh /2));

            double hisAngle2 = atan2( x, y);

            x = (_t->pos.fx + (_t->pos.fw))- (_e->pos.fx + (_e->pos.fw /2));

            y = (_t->pos.fy + (_t->pos.fh))- (_e->pos.fy + (_e->pos.fh /2));

            double hisAngle4 = atan2(x , y);

            result = (hisAngle1 > myAngle && hisAngle2 > myAngle && hisAngle3 > myAngle && hisAngle4 > myAngle) || (hisAngle1 < myAngle && hisAngle2 < myAngle && hisAngle3 < myAngle && hisAngle4 < myAngle);

            if(!result){
                _t->pos.r = 0;
                return false;   
            }

            _t->pos.r = 130;
        }
    }

    return canSee(dist, myAngle, _e,_el->_next);
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
        game.addEntity(new Hitbox(_renderer,pos.fx,pos.fy,30,30,TEAM_ENEMY_PRJECTILE,25*(cos(angle)),25*(sin(angle)),30,1,0));
        shootCd = 20;
    }
}