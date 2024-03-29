#pragma once
#include <texture.h>
#include <string>
#include <SDL.h>

extern TextureHandler textures;

class Cursor{

    public:
    
        SDL_Rect pos;
        SDL_Texture* _texture;
        SDL_Renderer* _renderer;

        Cursor(){
            SDL_ShowCursor(SDL_DISABLE);

            int *x = new int, *y = new int;

            SDL_GetMouseState(x,y);

            pos.x = *x;

            pos.y = *y;

            pos.w = 30;

            pos.h = 30;

            _renderer = NULL;

            _texture = textures._cursor;
        }

        void show();
};