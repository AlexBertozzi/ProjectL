#include <hud.h>

void HUD::show(){
    if(_tracking == NULL) return;

    SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);

    hpPos.w = (_tracking->hp / _tracking->maxHp) * hpLen;

    SDL_RenderFillRect(_renderer, &hpPos);
}