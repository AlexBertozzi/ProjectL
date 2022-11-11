#pragma once
#include <player.h>
#include <SDL.h>

class Sol : public Player{

    public:

        double inertia;

        double fireCd;

        double dashCd;

        double IFrames;

        Sol(SDL_Renderer* _r, int x, int y) : Player(_r,x,y,50,80){

            inertia = 0;
            dashCd = 0;
            fireCd = 0;

            IFrames = 0;
        }

        void update(double mod);

        void move(double mod);

        void dash();

        void specialDown(int key);

        void fire();

        void show();
};