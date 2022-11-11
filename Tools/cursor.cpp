#include <SDL.h>
#include <cursor.h>
#include <camera.h>

extern Camera camera;

void Cursor::show(){
    SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);

    int *x = new int, *y = new int;

    SDL_GetMouseState(x,y);

    pos.x = *x + camera.modX;

    pos.y = *y + camera.modY;

    SDL_RenderFillRect(_renderer, &pos);
}