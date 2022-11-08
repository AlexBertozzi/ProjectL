#include <player.h>
#include <iostream>
#include <game.h>

extern const int SCREENHEIGHT;
extern const int SCREENWIDTH;

void Player::update(float mod){

    move(mod);

    Entity::update(mod);
}

void Player::move(float mod){

    if(jump && !airborne){verticalSpeed = -(jumpHeight);} //doesen't need mod
    airborne = true;

    pos.fy += (verticalSpeed * mod);

    verticalSpeed += (gravity * mod);
    if(verticalSpeed > maxVerticalSpeed) verticalSpeed = maxVerticalSpeed;

    if(left) pos.fx -= (orizontalSpeed * mod);
    if(right) pos.fx += (orizontalSpeed * mod);

    if(pos.fx < 0) pos.fx = 0;
    if(pos.fy < 0) pos.fy = 0;
    if(pos.fx > SCREENWIDTH) pos.fx = SCREENWIDTH;
    if(pos.fy > SCREENHEIGHT) pos.fy = SCREENHEIGHT;
}

void Player::collided(Entity* _e){
    if(_e->team == 0){

        if((pos.fx+ (9*pos.fw/10)) <= (_e->pos.fx)){

            pos.fx = _e->pos.fx - pos.fw;
        }else if((_e->pos.fx+ _e->pos.fw) <= (pos.fx + (pos.fw/10))){

            pos.fx = _e->pos.fx + _e->pos.fw;            
        }else if(((pos.fy+ (9*pos.fh/10)) <= (_e->pos.fy)) && (verticalSpeed >= 0)){

            pos.fy = _e->pos.fy - pos.fh;
            verticalSpeed = 0;
            airborne = false;
        }else if(((_e->pos.fy+ _e->pos.fh)) <= (pos.fy + (pos.fw/10)) && (verticalSpeed <= 0)){

            pos.fy = _e->pos.fy + _e->pos.fh;
            verticalSpeed = 0;
        }

    }
}