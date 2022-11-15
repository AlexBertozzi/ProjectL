#include <terrain.h>
#include <SDL.h>
#include <SDL_image.h>
#include <camera.h>

extern Camera camera;

void Terrain::load(std::string path){

    SDL_Surface* _surf = IMG_Load(path.c_str());

    _texture = SDL_CreateTextureFromSurface(_renderer, _surf);

    SDL_FreeSurface(_surf);
}

void Terrain::show(){
    pos.x = pos.fx - camera.modX;
    pos.y = pos.fy - camera.modY;
    pos.w = pos.fw;
    pos.h = pos.fh;

    SDL_RenderCopy(_renderer,_texture, NULL, &pos);
}