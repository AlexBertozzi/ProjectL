#include <sol.h>
#include <game.h>
#include <hitbox.h>
#include <iostream>
#include <math.h>
#include <slash.h>
#include <camera.h>

extern Game game;
extern Camera camera;

void Sol::update(double mod){

    if(dashCd>=0) dashCd -= mod;
    if(fireCd>=0) fireCd -= mod;
    if(slashCd>=0) slashCd -= mod;
    if(IFrames>=0) IFrames -= mod;

    if(leftMouse) fire();
    else if(rightMouse) slash();

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

    double angle = atan2(game.cursor.pos.y-pos.fy + camera.modY, game.cursor.pos.x-pos.fx + camera.modX);

    double modx = 5*cos(angle);

    double mody = 5*sin(angle);

    game.addEntity(new Hitbox(_renderer,pos.fx,pos.fy,30,30,2,50*(modx),50*(mody),30,1));

    fireCd = 3;
}

void Sol::slash(){
    if(slashCd >0) return;

    double angle = atan2(game.cursor.pos.y-pos.fy + camera.modY, game.cursor.pos.x-pos.fx + camera.modX);

    double modx = 5*cos(angle - 0.2);
    double mody = 5*sin(angle - 0.2);

    Slash* first = new Slash(_renderer,10*modx,10*mody,30,30,2,0,0,0.7,1,this);

    modx = 5*cos(angle);
    mody = 5*sin(angle);

    first->concat(new Slash(_renderer,10*modx,10*mody,30,30,2,0,0,0.7,1,this));

    modx = 5*cos(angle + 0.2);
    mody = 5*sin(angle + 0.2);

    first->concat(new Hitbox(_renderer,10*modx,10*mody,30,30,2,0,0,0.7,1,this));

    game.addEntity(first);

    slashCd = 3;
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