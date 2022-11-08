#include "game.h"
#include <SDL.h>
#include <iostream>

extern int SCREENHEIGHT;
extern int SCREENWIDTH;

void Game::updateAllEntities(EntityList* _head, float mod){
    if(_head == NULL) return;

    _head->_e->update(mod);

    checkCollisions(_head,_head->_next);

    if(!_head->_e->alive){
        // delete the element
        EntityList* _box = _head;
        _head = _head->_next;
        delete(_box);
        updateAllEntities(_head,mod);
    }else{
        updateAllEntities(_head->_next,mod);
    }
}

void Game::checkCollisions(EntityList* _toCheck, EntityList* _next){

    if(_toCheck == NULL || _next == NULL){return;}

    _toCheck->_e->collision(_next->_e);

    checkCollisions(_toCheck,_next->_next);
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

    std::cout<<"DOWN: "<<key<<std::endl;

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

    std::cout<<"UP:   "<<key<<std::endl;

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

void Game::addEntity(Entity* _e){
    
    EntityList* _el = new EntityList;

    _el->_e = _e;
    _el->_next = _ELHead;

    _ELHead = _el;
}