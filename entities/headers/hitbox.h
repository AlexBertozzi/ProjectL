#pragma once

#include <entity.h>
#include <rect.h>
#include <SDL.h>

class Hitbox : public Entity{

    public:

        int orizontalSpeed, verticalSpeed;

        Entity* _following;

        double followDistanceX,followDistanceY;

        double duration, knockback;

        Hitbox(SDL_Renderer* _r,int x, int y, int w, int h, Team team, float oSpeed, float vSpeed, float duration, float damage ,float knock) : Entity(_r, x,y,w,h){
            this->team = team;

            orizontalSpeed = oSpeed;
            verticalSpeed = vSpeed;

            _following = NULL;
            followDistanceX = 0;
            followDistanceY = 0;

            knockback = knock;
            contactDamage = damage;

            pos.r = 255;
            pos.g = 0;
            pos.b = 0;

            this->duration = duration;
        }

        Hitbox(SDL_Renderer* _r,int x, int y, int w, int h, Team team, float oSpeed, float vSpeed, float duration, float damage, float knock, Entity* _e) : Entity(_r, 0,0,w,h){
            this->team = team;

            pos.fx = _e->pos.fx + x;
            pos.fy = _e->pos.fy + y;

            orizontalSpeed = oSpeed;
            verticalSpeed = vSpeed;

            _following = _e;
            followDistanceX = x;
            followDistanceY = y;

            knockback = knock;
            contactDamage = damage;

            pos.r = 255;
            pos.g = 0;
            pos.b = 0;

            this->duration = duration;
        }

        virtual ~Hitbox(){
            return;
        }

        virtual void update(double mod, EntityList* _h);

        void move(double mod, EntityList* _h);

        virtual void collided(Entity* _e);

        Hitbox* follow(Entity* _e, double distanceX, double distanceY);

};