#include <entity.h>
#include <SDL.h>

bool Entity::update(float mod){
    show();
    return true;
}

void Entity::show(){

    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

    SDL_RenderFillRect(_renderer, &pos);
}