#include <player.h>
#include <iostream>
#include <game.h>

extern const int SCREENHEIGHT;
extern const int SCREENWIDTH;

void Player::update(double mod){

    if(sleep >0) sleep -= mod;

    move(mod);

    Entity::update(mod);
}

void Player::move(double mod){

    double flyMod = 0;

    if(jump && !airborne){verticalSpeed = -(jumpHeight);} //doesen't need mod

    pos.fy += (verticalSpeed * mod);

    verticalSpeed += (gravity * mod);
    if(verticalSpeed > maxVerticalSpeed) verticalSpeed = maxVerticalSpeed;

    if(airborne > 0.3){
        if(sleep <= 0){

            if(left){ 
                flyMod = -(flySpeed * mod);
                direction = 'L';
            }

            else if(right){ 
                flyMod = (flySpeed * mod);
                direction = 'R';
            }
        }
    }else{
        if(sleep <= 0){

            if(down){
                crouch();
            }else{
                stand();
            }
            
            if(left){ 
                orizontalMomentum = -(orizontalSpeed);
                direction = 'L';
            }

            else if(right){ 
                orizontalMomentum = (orizontalSpeed);
                direction = 'R';
            }
            
            else{
                orizontalMomentum = 0;
            }
        }else{
            orizontalMomentum = 0;
        }
    }
    
    pos.fx += (orizontalMomentum * mod) + flyMod;
    
    if(pos.fx < 0) pos.fx = 0;
    if(pos.fy < 0) pos.fy = 0;
    if(pos.fx > SCREENWIDTH) pos.fx = SCREENWIDTH;
    if(pos.fy > SCREENHEIGHT) pos.fy = SCREENHEIGHT;

    airborne += mod;
}

void Player::collided(Entity* _e){
    if(_e->team == 0){

        if((pos.fx+ (9*pos.fw/10)) <= (_e->pos.fx)){

            pos.fx = _e->pos.fx - pos.fw;
        }else if((_e->pos.fx+ _e->pos.fw) <= (pos.fx + (pos.fw/10))){

            pos.fx = _e->pos.fx + _e->pos.fw;            
        }else if(((pos.fy+ (9*pos.fh/10)) <= (_e->pos.fy)) && (verticalSpeed >= 0)){

            pos.fy = _e->pos.fy - pos.fh;
            verticalSpeed = 0;
            airborne = 0;
        }else if(((_e->pos.fy+ _e->pos.fh)) <= (pos.fy + (pos.fw/10)) && (verticalSpeed <= 0)){

            pos.fy = _e->pos.fy + _e->pos.fh;
            verticalSpeed = 0;
        }

    }
}

void Player::keyDown(SDL_Scancode key){

    std::cout<<"DOWN: "<<key<<std::endl;

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
        case SDL_SCANCODE_SPACE:
            jump = true;
            break;

        default:
            if(!special(key)){
                normal(key);
            }
            break;
    }

    buffer.index += 1;

    buffer.buffer[(buffer.index % buffer.size)] = key;
}

void Player::keyUp(SDL_Scancode key){

    std::cout<<"UP:   "<<key<<std::endl;

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
        case SDL_SCANCODE_SPACE:
            jump = false;
            break;
        default:
            break;
    }
}

bool Player::checkBuffer(int size, int* toCheck){

    int index = 0;

    bool found = false;

    for(int i= 0; i< buffer.size; i++){
        if(buffer.buffer[(buffer.index + i +1) % buffer.size] == toCheck[index]){
            if(index < (size-1)){
                index++;
            }else{
                found = true;
            }
        }
    }

    return found;

}

bool Player::special(int button){
    return false;
}

void Player::normal(int button){
    return;
}

void Player::crouch(){
    return;
}

void Player::stand(){
    return;
}