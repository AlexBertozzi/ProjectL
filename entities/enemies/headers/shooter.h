#pragma once

#include <entity.h>
#include <SDL.h>
#include <game.h>

class Shooter : public Entity{

    public:

        double safe,speedX,speedY,hp, maxHp, shootCd;

        Shooter(SDL_Renderer* _r,int x, int y, int w, int h) : Entity(_r, x,y, w, h){
            team = -1;

            pos.r = 255;
            pos.g = 0;
            pos.b = 0;

            safe = 300;

            maxHp = 3;
            hp = maxHp;

            shootCd = 0;
        }

        void move(double mod);

        void update(double mod);

        void moveAwayAndShoot(EntityList* _head);

        void collided(Entity* _e);

        bool canSee(Entity* _e,EntityList* _el);
};