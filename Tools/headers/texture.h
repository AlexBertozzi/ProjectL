#pragma once
#include <string>
#include <SDL.h>

class TextureHandler{
    public:

        SDL_Renderer* _renderer;

        SDL_Texture* _terrain;
        SDL_Texture* _cursor;

        TextureHandler(){
        }

        void loadTerrain(std::string path);
        void loadCursor(std::string path);

        void loadAll(SDL_Renderer* _r);

};