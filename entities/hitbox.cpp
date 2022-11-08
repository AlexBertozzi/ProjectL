#include <hitbox.h>

void Hitbox::update(float mod){
    move(mod);
}

void Hitbox::move(float mod){
    pos.fx += (orizontalSpeed * mod);
    pos.fy += (verticalSpeed * mod);
}