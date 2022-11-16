#include <game.h>
#include <SDL.h>
#include <camera.h>
#include <iostream>

extern const int SCREENHEIGHT;
extern const int SCREENWIDTH;
extern const int CELLWIDTH ;
extern const int CELLHEIGHT;
extern const int MAPWIDTH;
extern const int MAPHEIGHT;
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
        delete(_box->_e);
        delete(_box);

        //don't need to progress the list, already on next element
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
            if(_event->key.keysym.scancode == SDL_SCANCODE_R){
                reload();
            }
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

void Game::createMap(){

    std::cout<<"Initializing map: ";

    char** map = new char*[MAPWIDTH];

    for(int x= 0; x< MAPWIDTH; x++){

        map[x] = new char[MAPHEIGHT];

        for(int y= 0; y< MAPHEIGHT; y++){
            map[x][y] = 'T';
        }
    }

    std::cout<<"Done"<<std::endl<<"Creating paths: ";

    createPath(map,MAPWIDTH/2,MAPHEIGHT/2,400,0);
    createPath(map,MAPWIDTH/2,MAPHEIGHT/2,400,1);
    createPath(map,MAPWIDTH/2,MAPHEIGHT/2,400,2);
    createPath(map,MAPWIDTH/2,MAPHEIGHT/2,400,3);
    createPath(map,MAPWIDTH/2,MAPHEIGHT/2,400,0);
    createPath(map,MAPWIDTH/2,MAPHEIGHT/2,400,1);
    createPath(map,MAPWIDTH/2,MAPHEIGHT/2,400,2);
    createPath(map,MAPWIDTH/2,MAPHEIGHT/2,400,3);

    std::cout<<"Done"<<std::endl<<"Placing entities: ";

    for(int x= 0; x< MAPWIDTH; x++){

        for(int y= 0; y< MAPHEIGHT; y++){
            
            switch(map[x][y]){
                case 'T':
                    addEntity(new Terrain(_renderer, (x*CELLWIDTH), (y*CELLHEIGHT), CELLWIDTH, CELLHEIGHT));
                    break;
                case 'S':
                    addEntity(new Shooter(_renderer,(x*CELLWIDTH), (y*CELLHEIGHT)));
                    break;
                default:
                    break;
            }
        }
    }

    std::cout<<"Done"<<std::endl;

    _player1->pos.fx = (MAPWIDTH * CELLWIDTH)/2;
    _player1->pos.fy = (MAPHEIGHT * CELLHEIGHT)/2;

}

void Game::createPath(char** map, int x, int y, int rem,int prev){
    if(x >= 0 && x < MAPWIDTH && y >= 0 && y < MAPHEIGHT && rem >= 0){

        if(rand()%10000 < 50)
            map[x][y] = 'S';
        else
            map[x][y] = ' ';

        int next = rand()%4;

        while(next == prev) next = rand()%4;

        switch(next){
            case 0:
                createPath(map,x+1,y,rem-1,next);
                break;
            case 1:
                createPath(map,x,y+1,rem-1,next);
                break;
            case 2:
                createPath(map,x-1,y,rem-1,next);
                break;
            default:
                createPath(map,x,y-1,rem-1,next);
                break;
        }
    }
}

void Game::reload(){
    clearEntities(_ELHead);

    _ELHead = NULL;

    addEntity(_player1);

    createMap();
}

void Game::clearEntities(EntityList* _head){
    if(_head == NULL) return;

    clearEntities(_head->_next);

    if(_head->_e->team != TEAM_PLAYER)
        delete(_head->_e);

    delete(_head);
}