#pragma once
#include "entity.h"
#include <SDL.h>

class Player : public Entity{

    public: 

        bool up,down,left,right,jump, airborne;

        float gravity,verticalSpeed, orizontalSpeed, maxVerticalSpeed, jumpHeight;

        Player(SDL_Renderer* _r, int x, int y, int w, int h) : Entity(_r,x,y,w,h){

            up = false;
            down = false;
            left = false;
            right = false;
            jump = false;
            airborne = false;
            verticalSpeed = 0;
            orizontalSpeed = 50;
            maxVerticalSpeed = 100;
            team = 1;
            jumpHeight = 100;
            gravity = 50;
        }

        void update(float mod);

        void move(float mod);

        void collided(Entity* _e);
};