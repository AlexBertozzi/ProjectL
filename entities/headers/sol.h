#pragma once
#include <player.h>
#include <SDL.h>

class Sol : public Player{

    public:

        Sol(SDL_Renderer* _r, int x, int y) : Player(_r,x,y,40,100){

        }

        void normal(int key);

        void heavy();
        void light();
};