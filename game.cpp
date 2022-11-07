#include "game.h"

void Game::loop(){
    return;
}

void Game::foreachEntity(void (*toDo)(Entity*)){
    if(_ELHead == nullptr){return;} 

    toDo(_ELHead->_e);

    doToNext(_ELHead->_next,toDo);
}

void Game::doToNext(EntityList* _el, void (*toDo)(Entity*)){
    if(_ELHead == nullptr){return;} 

    toDo(_ELHead->_e);

    doToNext(_ELHead->_next,toDo);
}