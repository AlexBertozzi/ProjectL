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
    dashCd = 1.7;
    IFrames = 0.7;
}

void Sol::fire(){

    if(fireCd >0) return;

    int *x = new int, *y = new int;

    SDL_GetMouseState(x,y);

    double angle = atan2(*y-pos.fy + camera.modY, *x-pos.fx + camera.modX);

    double modx = 5*cos(angle);

    double mody = 5*sin(angle);

    game.addEntity(new Hitbox(_renderer,pos.fx,pos.fy,30,30,2,50*(modx),50*(mody),30,1));

    fireCd = 3;
}

void Sol::show(){
    if(IFrames<= 0 || ((int)(IFrames*1000))%3 == 0) Entity::show();
}   

void Sol::collided(Entity* _e){
    if(_e->team <0){
        hp -= _e->contactDamage;
    }

    Player::collided(_e);
}