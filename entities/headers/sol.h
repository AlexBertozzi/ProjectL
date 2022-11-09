#pragma once
#include <player.h>
#include <SDL.h>

class Sol : public Player{

    public:

        double inertia;

        double tick;

        double dashCd;

        Sol(SDL_Renderer* _r, int x, int y) : Player(_r,x,y,50,80){

            inertia = 0;
            tick = -1;
            dashCd = 0;

        }

        void update(double mod);

        void move(double mod);

        void crouch();
        void stand();

        void normal(int key);

        void heavy();
        void light();

        void dash();
};