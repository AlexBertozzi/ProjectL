#pragma once

#include <entity.h>
#include <rect.h>
#include <SDL.h>

class Hitbox : public Entity{

    public:

        int orizontalSpeed, verticalSpeed;

        Entity* _following;

        double followDistanceX,followDistanceY;

        double duration;

        Hitbox(SDL_Renderer* _r,int x, int y, int w, int h, int team, float oSpeed, float vSpeed, float duration) : Entity(_r, x,y,w,h){
            this->team = team;

            orizontalSpeed = oSpeed;
            verticalSpeed = vSpeed;

            _following = NULL;
            followDistanceX = 0;
            followDistanceY = 0;

            pos.r = 255;
            pos.g = 0;
            pos.b = 0;

            this->duration = duration;
        }

        Hitbox(SDL_Renderer* _r,int x, int y, int w, int h, int team, float oSpeed, float vSpeed, float duration, Entity* _e) : Entity(_r, x,y,w,h){
            this->team = team;

            orizontalSpeed = oSpeed;
            verticalSpeed = vSpeed;

            _following = _e;
            followDistanceX = x;
            followDistanceY = y;

            pos.r = 255;
            pos.g = 0;
            pos.b = 0;

            this->duration = duration;
        }

        void update(double mod);

        void move(double mod);

        void collided(Entity* _e);

        Hitbox* follow(Entity* _e, double distanceX, double distanceY);

};