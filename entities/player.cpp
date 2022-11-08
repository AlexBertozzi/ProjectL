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

    if(up){verticalSpeed = -(jumpHeight);} //doesen't need mod

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

        if(((pos.fy+ (9*pos.fh/10)) < (_e->pos.fy)) && (verticalSpeed >= 0)){
            pos.fy = _e->pos.fy - pos.fh;
            verticalSpeed = 0;
        }

        if(((_e->pos.fy+ (9*_e->pos.fh/10)) < (pos.fy)) && (verticalSpeed <= 0)){
            pos.fy = _e->pos.fy + _e->pos.fh;
            verticalSpeed = 0;
        }

    }
}