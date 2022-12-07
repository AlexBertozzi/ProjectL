#pragma once
#include <SDL.h>
#include <rect.h>
#include <teams.h>

struct EntityList;

class Entity{

    public: 

        Rect pos;

        Team team;

        SDL_Renderer* _renderer;

        virtual void update(double mod, EntityList* _head);

        virtual void show();

        bool alive;

        float contactDamage;

        Entity(SDL_Renderer* _r,int x, int y, int w, int h){
            pos.fx = x;
            pos.fy = y;
            pos.fh = h;
            pos.fw = w;

            _renderer = _r;
            team = TEAM_DECORATION;
            alive = true;

            contactDamage = 0;

            pos.r = 255;
            pos.g = 255;
            pos.b = 255;
        }

        virtual ~Entity(){
            return;
        }

        virtual void checkCollisions(EntityList* _entities);

        virtual void collision(Entity* _e);

        virtual void collided(Entity* _e);

};

struct EntityList{
    Entity* _e;
    EntityList* _next;
};