#include <sol.h>
#include <game.h>
#include <hitbox.h>
#include <iostream>
#include <math.h>
#include <camera.h>

extern Game game;
extern Camera camera;

void Sol::update(double mod){

    if(dashCd>=0) dashCd -= mod;
    if(fireCd>=0) fireCd -= mod;
    if(IFrames>=0) IFrames -= mod;

    if(leftMouse) fire();

    Player::update(mod);
}

void Sol::move(double mod){

    if(inertia > 0){

        if(up) pos.fy -= inertia*mod / (left || right ? 2 : 1);
        if(down) pos.fy += inertia*mod / (left || right ? 2 : 1);
        if(left) pos.fx -= inertia*mod / (up || down ? 2 : 1);
        if(right) pos.fx += inertia*mod / (up || down ? 2 : 1);

        inertia -= ((inertia+speed)*mod)/3;
    }
    

    Player::move(mod);
}

void Sol::specialDown(int key){
    switch(key){
        case SDL_SCANCODE_SPACE:
            dash();
            break;
        default:
            break;
    }
}

void Sol::dash(){
    if(dashCd > 0) return;
    inertia = 100;
    dashCd = 1.5;
    IFrames = 0.7;
}

void Sol::fire(){

    if(fireCd >0) return;

    int *x = new int, *y = new int;

    SDL_GetMouseState(x,y);

    double angle = atan2(*y-pos.fy + camera.modY, *x-pos.fx + camera.modX) * (180/3.141592654);

    double modx = 5*cos(angle/(180/3.141592654));

    double mody = 5*sin(angle/(180/3.141592654));

    game.addEntity(new Hitbox(_renderer,pos.fx,pos.fy,30,30,team,50*(modx),50*(mody),30));

    fireCd = 1.5;
}

void Sol::show(){
    if(IFrames<= 0 || ((int)(IFrames*1000))%3 == 0) Entity::show();

    
}   