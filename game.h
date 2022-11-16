#pragma once

#include <texture.h>
#include <entity.h>
#include <SDL.h>
#include <sol.h>
#include <terrain.h>
#include <camera.h>
#include <cursor.h>
#include <hud.h>
#include <shooter.h>
#include <ctime>
#include <iostream>

extern const int SCREENWIDTH;
extern const int SCREENHEIGHT;

const int CELLWIDTH = 60;
const int CELLHEIGHT = CELLWIDTH;

const int MAPWIDTH = 25;
const int MAPHEIGHT = MAPWIDTH;

extern TextureHandler textures;
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

            srand(time(NULL));

            _renderer = _r;
            lastTick = SDL_GetTicks();
            _ELHead = NULL;

            std::cout<<"Loading textures: ";
            textures.loadAll(_r);
            std::cout<<"Done"<<std::endl;

            cursor = Cursor();
            cursor._renderer = _r;

            _player1 = new Sol(_renderer,-100,-100);
            addEntity(_player1);

            createMap();
            
            hud = HUD();
            hud._tracking = _player1;
            hud._renderer = _r;
            camera = Camera(_player1,MAPWIDTH*CELLWIDTH,MAPHEIGHT*CELLHEIGHT);
        }

        void addEntity(Entity* _e);

        SDL_Renderer* _renderer;

    private:        

        void handleEvent(SDL_Event* _event);

        void checkCollisions(EntityList* _toCheck, EntityList* _next);

        void createMap();

        void createPath(char** map, int x, int y, int rem, int prev);

        void reload();

        void clearEntities(EntityList* _head);
};