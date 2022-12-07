#pragma once

#include <teams.h>
#include <entity.h>
#include <SDL.h>
#include <game.h>

class Shooter : public Entity{

    public:

        double safe,speedX,speedY,hp, maxHp, shootCd;

        SDL_Rect lastPlayerPos;

        char state;

        Shooter(SDL_Renderer* _r,int x, int y) : Entity(_r, x,y, 45, 45){
            team = TEAM_ENEMY;

            pos.r = 255;
            pos.g = 0;
            pos.b = 0;

            safe = 300;

            lastPlayerPos.x = -1;
            lastPlayerPos.y = -1;
            lastPlayerPos.w = 10;
            lastPlayerPos.h = 10;

            maxHp = 5;
            hp = maxHp;

            shootCd = 0;
            state = 'i'; //idle
        }

        void move(double mod, EntityList* _h);

        void update(double mod, EntityList* _h);

        void switchMode(EntityList* _head);

        void moveAwayAndShoot();
        void idle();
        void search();

        void collided(Entity* _e);

        bool canSee(double dist, double myAngle, Entity* _e,EntityList* _el);
};