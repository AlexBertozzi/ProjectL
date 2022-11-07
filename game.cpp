#include "game.h"
#include <SDL.h>

extern int SCREENHEIGHT;
extern int SCREENWIDTH;

void Game::updateAllEntities(EntityList* _head, float mod){
    if(_head == NULL) return;

    if(!(_head->_e->update(mod))){
        EntityList* _box = _head;
        _head = _head->_next;
        delete(_box);
        updateAllEntities(_head,mod);
    }else{
        updateAllEntities(_head->_next,mod);
    }

    
}

void Game::loop(){

    float dT = (SDL_GetTicks()-lastTick)/100.0f;
    lastTick = SDL_GetTicks();
    
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    updateAllEntities(_ELHead,dT);

    SDL_RenderPresent(_renderer);
}