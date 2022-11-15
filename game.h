#pragma once

#include <entity.h>
#include <SDL.h>
#include <sol.h>
#include <terrain.h>
#include <camera.h>
#include <cursor.h>
#include <hud.h>
#include <shooter.h>

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

        HUD hud;

        Cursor cursor;

        Game(){}

        Game(SDL_Renderer* _r){

            _renderer = _r;
            lastTick = SDL_GetTicks();
            _ELHead = NULL;

            cursor = Cursor();
            cursor._renderer = _r;
            cursor.load("png/crossair_thick.png");

            _player1 = new Sol(_renderer,50,50);
            addEntity(_player1);
            
            hud = HUD();
            hud._tracking = _player1;
            hud._renderer = _r;
            camera = Camera(_player1,10000,10000);

            addEntity(new Shooter(_r, 700,1000,50,50));

            addEntity(new Terrain(_renderer,1000,SCREENHEIGHT-100,50,55));
            addEntity(new Terrain(_renderer,0,SCREENHEIGHT-50,SCREENWIDTH,50));
        }

        void addEntity(Entity* _e);

        SDL_Renderer* _renderer;

    private:        

        void handleEvent(SDL_Event* _event);

        void checkCollisions(EntityList* _toCheck, EntityList* _next);
};