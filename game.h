#pragma once

#include <entity.h>
#include <SDL.h>

class Game{

    public:

        EntityList* _ELHead;

        int lastTick;

        void loop();

        void updateAllEntities(EntityList* _head, float mod);

        Game(SDL_Renderer* _r){
            _renderer = _r;
            lastTick = SDL_GetTicks();
            _ELHead = NULL;
        }

    private:

        SDL_Renderer* _renderer;
};