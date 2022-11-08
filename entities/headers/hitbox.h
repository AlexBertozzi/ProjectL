#pragma once

#include <entity.h>
#include <rect.h>

class Hitbox : public Entity{

    public:

        int orizontalSpeed, verticalSpeed;

        Hitbox(int x, int y, int w, int h, int team, float oSpeed, float vSpeed) : Entity(NULL, x,y,w,h){
            this->team = team;

            orizontalSpeed = oSpeed;
            verticalSpeed = vSpeed;

            pos.r = 255;
            pos.g = 0;
            pos.b = 0;
        }

        void update(float mod);

        void move(float mod);

};