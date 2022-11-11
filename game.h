#pragma once

#include <entity.h>
#include <SDL.h>
#include <sol.h>
#include <terrain.h>
#include <camera.h>
#include <cursor.h>

extern const int SCREENWIDTH;
extern const int SCREENHEIGHT;

extern Camera camera;

class Game{

    public:

        EntityList* _ELHead;

        int lastTick;

        void loop(SDL_Event* _event);

        void updateAllEntities(EntityList* &_head, float mod);

        Player* _player1;

        Cursor cursor;

        Game(){}

        Game(SDL_Renderer* _r){

            _renderer = _r;
            lastTick = SDL_GetTicks();
            _ELHead = NULL;

            cursor = Cursor();
            cursor._renderer = _r;

            _player1 = new Sol(_renderer,50,50);
            addEntity(_player1);

            camera = Camera(_player1,10000,10000);

            addEntity(new Terrain(_renderer,1000,SCREENHEIGHT-100,50,50));
            addEntity(new Terrain(_renderer,0,SCREENHEIGHT-50,SCREENWIDTH,50));
        }

        void addEntity(Entity* _e);

        SDL_Renderer* _renderer;

    private:        

        void handleEvent(SDL_Event* _event);

        void checkCollisions(EntityList* _toCheck, EntityList* _next);
};