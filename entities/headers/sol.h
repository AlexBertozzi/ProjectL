#pragma once
#include <player.h>
#include <SDL.h>

class Sol : public Player{

    public:

        double inertia;

        double fireCd;

        double dashCd;

        double IFrames;

        Sol(SDL_Renderer* _r, int x, int y) : Player(_r,x,y,25,25){

            inertia = 0;
            dashCd = 0;
            fireCd = 0;

            IFrames = 0;

            maxHp = 5;
            hp = 5;
        }

        void update(double mod);

        void move(double mod);

        void dash();

        void specialDown(int key);

        void fire();

        void show();

        void collided(Entity* _e);
};