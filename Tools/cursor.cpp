#include <string>

#include <SDL.h>
#include <cursor.h>
#include <camera.h>
#include <SDL_image.h>

extern Camera camera;

void Cursor::load(std::string path){

    SDL_Surface* _surf = IMG_Load(path.c_str());

    _texture = SDL_CreateTextureFromSurface(_renderer, _surf);

    SDL_FreeSurface(_surf);
}

void Cursor::show(){
    SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);

    int *x = new int, *y = new int;

    SDL_GetMouseState(x,y);

    pos.x = *x - 16;

    pos.y = *y - 16;

    SDL_RenderCopy(_renderer,_texture, NULL, &pos);
}