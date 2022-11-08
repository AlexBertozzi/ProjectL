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
        }

        void update(float mod);

        void move(float mod);

};