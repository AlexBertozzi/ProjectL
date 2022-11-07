#pragma once

#include <entity.h>
#include <SDL.h>
#include <player.h>

class Game{

    public:

        EntityList* _ELHead;

        int lastTick;

        void loop(SDL_Event* _event);

        void updateAllEntities(EntityList* _head, float mod);

        Player* _player1;

        Game(SDL_Renderer* _r){
            _renderer = _r;
            lastTick = SDL_GetTicks();
            _player1 = new Player(_renderer,50,50,50,50);

            _ELHead = new EntityList{_player1,NULL};
        }

    private:

        SDL_Renderer* _renderer;

        void handleEvent(SDL_Event* _event);

        void keyDown(SDL_Scancode key);
        void keyUp(SDL_Scancode key);
};