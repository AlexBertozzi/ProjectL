#pragma once

#include <entity.h>
#include <SDL.h>

class Game{

    public:

        EntityList* _ELHead;

        void loop();

        void foreachEntity(void (*toDo)(Entity*));

        Game(SDL_Surface* _s){
            _surface = _s;
        }

    private:

       void doToNext(EntityList* _el, void (*toDo)(Entity*));

       SDL_Surface* _surface;
};