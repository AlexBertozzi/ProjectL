#include <player.h>
#include <iostream>

bool Player::update(float mod){

    move(mod);

    return Entity::update(mod);
}

void Player::move(float mod){
    if(up) pos.fy -= (verticalSpeed * mod);

    if(down) pos.fy += (verticalSpeed * mod);

    if(left) pos.fx -= (orizontalSpeed * mod);

    if(right) pos.fx += (orizontalSpeed * mod);
}