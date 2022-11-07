#pragma once
#include "entity.h"
#include <SDL.h>

class Player : Entity{

    bool up,down,left,right;

    int verticalSpeed, orizontalSpeed;

    Player(SDL_Renderer* _r, int x, int y, int w, int h) : Entity(_r,x,y,w,h){

        up = false;
        down = false;
        left = false;
        right = false;
        verticalSpeed = 5;
        orizontalSpeed = 5;
    }

    void update(float mod);

    void move(float mod);
};