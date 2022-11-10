#include <sol.h>
#include <game.h>
#include <hitbox.h>
#include <iostream>

extern Game game;

void Sol::update(double mod){
    if(tick >= 0){
        tick += mod;
    }

    if(dashCd>=0) dashCd -= mod;

    switch(status){
        case 'h':
            heavy();
            break;
        case 'f':
            fireball();
            break;
        default:
            break;
    }

    Player::update(mod);
}

void Sol::normal(int key){

    if(sleep > 0) return;

    switch(key){
        case SDL_SCANCODE_B:
            light();
            break;
        case SDL_SCANCODE_J:
            heavy();
            break;
        case SDL_SCANCODE_K:
            dash();
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

    if(status == ' ' && tick <0){

        status = 'h';
        tick = 0;

        inertia += direction == 'L'? -30 : 30;
        sleep = 3.65;

    }else if(status == 'h' && tick >=0.65){

        if(direction == 'L'){
            game.addEntity((new Hitbox(_renderer,-60,15,60,40,team,0,0,3,this)));
        }else{
            game.addEntity((new Hitbox(_renderer,pos.fw,15,60,40,team,0,0,3,this)));
        }
        
        tick = -1;
        status = ' ';
    }
}

void Sol::fireball(){
    if(status == ' ' && tick <0){
        status = 'f';
        tick = 0;

        inertia -= direction == 'L'? -15:15;
        sleep = 1.5;
    }else if(status == 'f' && tick >= 0.2){
        if(direction == 'L'){
            game.addEntity((new Hitbox(_renderer,pos.fx-20,pos.fy,20,20,team,-60,0,10)));
        }else{
            game.addEntity((new Hitbox(_renderer,pos.fx+pos.fw,pos.fy,20,20,team,60,0,10)));
        }
        
        tick = -1;
        status = ' ';
    }
}

void Sol::crouch(){
    if(!crouched){
        pos.fh = pos.fh/2;
        pos.fy += pos.fh;
        crouched = true;
    }
}

void Sol::stand(){
    if(crouched){
        pos.fy -= pos.fh;
        pos.fh = pos.fh*2;
        crouched = false;
    }
}

void Sol::move(double mod){

    if(inertia > 1 || inertia < 1){
        pos.fx += inertia * mod;

        inertia -= (inertia*mod);
    }
    

    Player::move(mod);
}

void Sol::dash(){
    if(dashCd > 0) return;
    if(direction == 'L'){
        inertia -= 100;
    }else{
        inertia = 100;
    }
    dashCd = 1;
}

bool Sol::special(int key){

    bool flag = false;

    switch(key){
        case SDL_SCANCODE_B:
            if(Player::checkBuffer(2, new int[2]{3,6}) || Player::checkBuffer(2, new int[2]{2,6})){
                direction = 'R';
                fireball();
                flag = true;
            }
            if(Player::checkBuffer(2, new int[2]{1,4}) || Player::checkBuffer(2, new int[2]{2,4})){
                direction = 'L';
                fireball();
                flag = true;
            }
            break;
        default:
            break;
    }

    return flag;
}