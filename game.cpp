#include "game.h"
#include <SDL.h>
#include <iostream>

extern int SCREENHEIGHT;
extern int SCREENWIDTH;

void Game::updateAllEntities(EntityList* _head, float mod){
    if(_head == NULL) return;

    if(!(_head->_e->update(mod))){
        // delete the element
        EntityList* _box = _head;
        _head = _head->_next;
        delete(_box);
        updateAllEntities(_head,mod);
    }else{

        updateAllEntities(_head->_next,mod);
    }
}

void Game::loop(SDL_Event* _event){

    handleEvent(_event);

    float dT = (SDL_GetTicks64()-lastTick)/100.0f;
    lastTick = SDL_GetTicks64();
    
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    updateAllEntities(_ELHead,dT);

    SDL_RenderPresent(_renderer);
}

void Game::keyDown(SDL_Scancode key){

    switch(key){
        case SDL_SCANCODE_W:
            _player1->up = true;
            break;
        case SDL_SCANCODE_A:
            _player1->left = true;
            break;
        case SDL_SCANCODE_S:
            _player1->down = true;
            break;
        case SDL_SCANCODE_D:
            _player1->right = true;
            break;
        default:
            break;
    }
}

void Game::keyUp(SDL_Scancode key){

    switch(key){
        case SDL_SCANCODE_W:
            _player1->up = false;
            break;
        case SDL_SCANCODE_A:
            _player1->left = false;
            break;
        case SDL_SCANCODE_S:
            _player1->down = false;
            break;
        case SDL_SCANCODE_D:
            _player1->right = false;
            break;
        default:
            break;
    }
}

void Game::handleEvent(SDL_Event* _event){

    switch(_event->type){
        case SDL_KEYDOWN:
            keyDown(_event->key.keysym.scancode);
            break;
        case SDL_KEYUP:
            keyUp(_event->key.keysym.scancode);
            break;
        default:
            break;
    }
}