#pragma once

#include <teams.h>
#include <texture.h>
#include <entity.h>
#include <string>

extern TextureHandler textures;

class Terrain : public Entity{

    public:

        SDL_Texture* _texture;
        
        Terrain(SDL_Renderer* _r,int x, int y, int w, int h) : Entity(_r,x,y,w,h){
            team = TEAM_TERRAIN;
            pos.r = 130;
            pos.b = 12;
            pos.g = 41;
            _texture = textures._terrain;
        }

        //void show();
};