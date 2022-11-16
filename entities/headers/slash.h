#pragma once

#include <entity.h>
#include <hitbox.h>
#include <SDL.h>

class Slash : public Hitbox{

    public:

        Hitbox* _next;

        Slash(SDL_Renderer* _r,int x, int y, int w, int h, int team, float oSpeed, float vSpeed, float duration, float damage, float knock) : Hitbox(_r,x,y,w,h,team,oSpeed,vSpeed,duration,damage,knock){
            _next = NULL;
        }

        Slash(SDL_Renderer* _r,int x, int y, int w, int h, int team, float oSpeed, float vSpeed, float duration, float damage, float knock, Entity* _e) : Hitbox(_r,x,y,w,h,team,oSpeed,vSpeed,duration,damage,knock, _e){
            _next = NULL;
        }

        ~Slash(){
            if(_next != NULL)
                delete(_next);
        }

        Slash* concat(Hitbox* _h);

        void update(double mod);
};