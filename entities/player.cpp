#include <player.h>
#include <iostream>

void Player::update(float mod){

    move(mod);

    Entity::update(mod);
}

void Player::move(float mod){
    if(up) pos.fy -= (verticalSpeed * mod);

    if(down) pos.fy += (verticalSpeed * mod);

    if(left) pos.fx -= (orizontalSpeed * mod);

    if(right) pos.fx += (orizontalSpeed * mod);
}

void Player::collided(Entity* _e){
    pos.g = 0;
    pos.b = 0;
}