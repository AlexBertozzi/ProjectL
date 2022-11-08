#pragma once

#include <entity.h>
#include <SDL.h>
#include <player.h>
#include <terrain.h>

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
            _ELHead = NULL;

            _player1 = new Player(_renderer,50,50,50,50);
            addEntity(_player1);
            addEntity(new Terrain(_renderer,100,100,100,100));
        }

        void addEntity(Entity* _e);

    private:

        SDL_Renderer* _renderer;

        void handleEvent(SDL_Event* _event);

        void keyDown(SDL_Scancode key);
        void keyUp(SDL_Scancode key);

        void checkCollisions(EntityList* _toCheck, EntityList* _next);
};