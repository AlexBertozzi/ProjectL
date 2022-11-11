#include <game.h>
#include <SDL.h>
#include <camera.h>
#include <iostream>

extern const int SCREENHEIGHT;
extern const int SCREENWIDTH;
extern Camera camera;

void Game::updateAllEntities(EntityList* &_head, float mod){
    if(_head == NULL) return;

    _head->_e->update(mod);

    checkCollisions(_head,_head->_next);

    if(_head->_e->alive){

        updateAllEntities(_head->_next,mod);
    }else{
        
        // delete the element
        EntityList* _box = _head;
        _head = _head->_next;
        delete(_box);
        updateAllEntities(_head,mod);
    }
}

void Game::checkCollisions(EntityList* _toCheck, EntityList* _next){

    if(_toCheck == NULL || _next == NULL){return;}

    _toCheck->_e->collision(_next->_e);

    checkCollisions(_toCheck,_next->_next);
}

void Game::loop(SDL_Event* _event){
    handleEvent(_event);

    double dT = (SDL_GetTicks64()-lastTick)/100.0f;
    lastTick = SDL_GetTicks64();
    
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    updateAllEntities(_ELHead,dT);

    camera.update();
    hud.show();
    cursor.show();

    SDL_RenderPresent(_renderer);
}

void Game::handleEvent(SDL_Event* _event){

    switch(_event->type){
        case SDL_KEYDOWN:
            _player1->keyDown(_event->key.keysym.scancode);
            break;
        case SDL_KEYUP:
            _player1->keyUp(_event->key.keysym.scancode);
            break;
        case SDL_MOUSEBUTTONDOWN:
            _player1->click(_event->button);
            break;
        case SDL_MOUSEBUTTONUP:
            _player1->click(_event->button);
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