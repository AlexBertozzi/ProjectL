#include <teams.h>
#include <player.h>
#include <iostream>
#include <game.h>
#include <buffer.h>

extern const int SCREENHEIGHT;
extern const int SCREENWIDTH;

void Player::update(double mod, EntityList* _h){

    if(sleep >0) sleep -= mod;

    move(mod,_h);

    Entity::update(mod,_h);
}

void Player::move(double mod, EntityList* _h){

    double distX = 0, distY = 0;

    if(up){
        distY -= (speed * mod) / (left || right ? 2 : 1);
    }
    if(left){
        distX -= (speed * mod) / (up || down ? 2 : 1);
    } 
    if(down){
        distY += (speed * mod) / (left || right ? 2 : 1);
    } 
    if(right){
        distX += (speed * mod) / (up || down ? 2 : 1);
    }

    while(distX != 0 || distY != 0){

        if(distX >= pos.fw){
            pos.fx += pos.fw;
            distX -= pos.fw;
        }else if(distX <= -pos.fw){
            pos.fx -= pos.fw;
            distX += pos.fw;
        }else{
            pos.fx += distX;
            distX = 0;
        }

        if(distY >= pos.fh){
            pos.fy += pos.fh;
            distY -= pos.fh;
        }else if(distY <= -pos.fh){
            pos.fy -= pos.fh;
            distY += pos.fh;
        }else{
            pos.fy += distY;
            distY = 0;
        }

        Entity::checkCollisions(_h);
    }   
        
    if(pos.fx < 0) pos.fx = 0;
    if(pos.fy < 0) pos.fy = 0;
    if(pos.fx > camera.maxX) pos.fx = camera.maxX - pos.fw;
    if(pos.fy > camera.maxY) pos.fy = camera.maxY - pos.fh;
}

void Player::collided(Entity* _e){
    if(_e->team == TEAM_TERRAIN || _e->team == TEAM_ENEMY){

        if((pos.fx+ (2*pos.fw/3)) <= (_e->pos.fx)){

            pos.fx = _e->pos.fx - pos.fw;
        }else if((_e->pos.fx+ _e->pos.fw) <= (pos.fx + (pos.fw/3))){

            pos.fx = _e->pos.fx + _e->pos.fw;            
        }else if(((pos.fy+ (2*pos.fh/3)) <= (_e->pos.fy))){

            pos.fy = _e->pos.fy - pos.fh;
        }else if(((_e->pos.fy+ _e->pos.fh)) <= (pos.fy + (pos.fw/3))){

            pos.fy = _e->pos.fy + _e->pos.fh;
        }
    }
}

void Player::keyDown(SDL_Scancode key){

    switch(key){
        case SDL_SCANCODE_W:
            up = true;
            break;
        case SDL_SCANCODE_A:
            left = true;
            break;
        case SDL_SCANCODE_S:
            down = true;
            break;
        case SDL_SCANCODE_D:
            right = true;
            break;
        default:
            specialDown(key);
            break;
    }
}

void Player::keyUp(SDL_Scancode key){

    switch(key){
        case SDL_SCANCODE_W:
            up = false;
            break;
        case SDL_SCANCODE_A:
            left = false;
            break;
        case SDL_SCANCODE_S:
            down = false;
            break;
        case SDL_SCANCODE_D:
            right = false;
            break;
        default:
            specialUp(key);
            break;
    }
}

void Player::click(SDL_MouseButtonEvent button){
    switch(button.button){
        case 1:
            leftMouse = button.state==SDL_PRESSED? true : false;
            break;
        case 3:
            rightMouse = button.state==SDL_PRESSED? true : false;
            break;
        default:
            break;
    }
}

void Player::specialDown(int key){
    return;
}

void Player::specialUp(int key){
    return;
}