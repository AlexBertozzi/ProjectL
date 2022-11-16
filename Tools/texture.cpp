#include <texture.h>
#include <SDL.h>
#include <string>
#include <SDL_image.h>

void TextureHandler::loadTerrain(std::string path){
    SDL_Surface* _surf = IMG_Load(path.c_str());

    _terrain = SDL_CreateTextureFromSurface(_renderer, _surf);

    SDL_FreeSurface(_surf);
}

void TextureHandler::loadCursor(std::string path){
    SDL_Surface* _surf = IMG_Load(path.c_str());

    _cursor = SDL_CreateTextureFromSurface(_renderer, _surf);

    SDL_FreeSurface(_surf);
}

void TextureHandler::loadAll(SDL_Renderer* _r){
    _renderer = _r;
    loadTerrain("png/terrain.png");
    loadCursor("png/crossair_thick.png");
}