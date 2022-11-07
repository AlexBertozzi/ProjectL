#include <player.h>
#include <iostream>

bool Player::update(float mod){

    move(mod);

    return Entity::update(mod);
}

void Player::move(float mod){
    if(up) pos.y -= verticalSpeed * mod;

    if(down) pos.y += verticalSpeed * mod;

    if(left) pos.x -= orizontalSpeed * mod;

    if(right) pos.x += orizontalSpeed * mod;
}