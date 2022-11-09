#include <sol.h>
#include <game.h>
#include <hitbox.h>
#include <iostream>

extern Game game;

void Sol::normal(int key){

    if(sleep > 0) return;

    switch(key){
        case SDL_SCANCODE_H:
            light();
            break;
        case SDL_SCANCODE_J:
            heavy();
            break;
        default:
            break;
    }
}

void Sol::light(){
    if(direction == 'L')
        game.addEntity((new Hitbox(_renderer,-40,10,40,40,team,0,0,2,this)));
    else
        game.addEntity(new Hitbox(_renderer,pos.fw,10,40,40,team,0,0,2,this));
    sleep = 2;
}

void Sol::heavy(){
    if(direction == 'L')
        game.addEntity((new Hitbox(_renderer,-60,15,60,40,team,0,0,4,this)));
    else
        game.addEntity((new Hitbox(_renderer,pos.fw,15,60,40,team,0,0,4,this)));
    sleep = 4;
}