#pragma once
#include <SDL.h>
#include <rect.h>

class Entity{

    public: 

        Rect pos;

        int team;

        SDL_Renderer* _renderer;

        virtual void update(float mod);

        virtual void show();

        bool alive;

        Entity(SDL_Renderer* _r,int x, int y, int w, int h){
            pos.fx = x;
            pos.fy = y;
            pos.fh = h;
            pos.fw = w;

            _renderer = _r;
            team = -1;
            alive = true;

            pos.r = 255;
            pos.g = 255;
            pos.b = 255;
        }

        void collision(Entity* _e);

        virtual void collided(Entity* _e);

};

struct EntityList{
    Entity* _e;
    EntityList* _next;
};