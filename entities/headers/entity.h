#pragma once
#include <SDL.h>

class Entity{

    public: 

        SDL_Rect pos;

        int team;

        SDL_Renderer* _renderer;

        bool update(float mod);

        void show();

    Entity(SDL_Renderer* _r,int x, int y, int w, int h){
        pos.x = x;
        pos.y = y;
        pos.h = h;
        pos.w = w;
        _renderer = _r;
    }

};

struct EntityList{
    Entity* _e;
    EntityList* _next;
};