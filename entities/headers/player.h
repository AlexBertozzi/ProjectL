#pragma once
#include "entity.h"
#include <SDL.h>

class Player : public Entity{

    public: 

        bool up,down,left,right;

        int verticalSpeed, orizontalSpeed;

        Player(SDL_Renderer* _r, int x, int y, int w, int h) : Entity(_r,x,y,w,h){

            up = false;
            down = false;
            left = false;
            right = false;
            verticalSpeed = 50;
            orizontalSpeed = 50;
            team = 1;
        }

        void update(float mod);

        void move(float mod);

        void collided(Entity* _e);
};