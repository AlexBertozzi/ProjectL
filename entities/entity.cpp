#include <entity.h>
#include <SDL.h>

void Entity::update(float mod){
    show();
}

void Entity::show(){

    SDL_SetRenderDrawColor(_renderer, pos.r, pos.g, pos.b, 255);

    pos.x = pos.fx;
    pos.y = pos.fy;
    pos.h = pos.fh;
    pos.w = pos.fw;

    SDL_RenderFillRect(_renderer, &pos);
}

void Entity::collision(Entity* _e){

    if((_e->pos.x < pos.x+pos.w) && (_e->pos.x+_e->pos.w > pos.x)){
        if((_e->pos.y < pos.y+pos.h) && (_e->pos.y+_e->pos.h > pos.y)){

            collided(_e);
            _e->collided(this);
        }
    }

}

void Entity::collided(Entity* _e){
    return;
}