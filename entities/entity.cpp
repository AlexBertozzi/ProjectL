#include <entity.h>
#include <SDL.h>
#include <camera.h>

extern Camera camera;

void Entity::update(double mod, EntityList* _e){
    show();
}

void Entity::show(){

    SDL_SetRenderDrawColor(_renderer, pos.r, pos.g, pos.b, 255);

    pos.x = pos.fx - camera.modX;
    pos.y = pos.fy - camera.modY;
    pos.h = pos.fh;
    pos.w = pos.fw;

    SDL_RenderFillRect(_renderer, &pos);
}

void Entity::collision(Entity* _e){

    if(_e == this) return;

    if((_e->pos.fx < pos.fx+pos.fw) && (_e->pos.fx+_e->pos.fw > pos.fx)){
        if((_e->pos.fy < pos.fy+pos.fh) && (_e->pos.fy+_e->pos.fh > pos.fy)){

            collided(_e);
            _e->collided(this);
        }
    }

}

void Entity::checkCollisions(EntityList* _entities){
    if(_entities == NULL) return;

    collision(_entities->_e);

    checkCollisions(_entities->_next);
}

void Entity::collided(Entity* _e){
    return;
}