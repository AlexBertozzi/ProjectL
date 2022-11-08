#include <entity.h>
#include <SDL.h>

bool Entity::update(float mod){
    show();
    return true;
}

void Entity::show(){

    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

    pos.x = pos.fx;
    pos.y = pos.fy;
    pos.h = pos.fh;
    pos.w = pos.fw;

    SDL_RenderFillRect(_renderer, &pos);
}