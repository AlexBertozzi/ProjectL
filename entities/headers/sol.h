#pragma once
#include <player.h>
#include <SDL.h>

class Sol : public Player{

    public:

        double inertia;


        double dashCd;

        Sol(SDL_Renderer* _r, int x, int y) : Player(_r,x,y,50,80){

            inertia = 0;
            dashCd = 0;
        }

        void update(double mod);

        void move(double mod);

        void dash();

        void specialDown(int key);

        void fire();
};