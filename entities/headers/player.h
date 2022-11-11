#pragma once
#include <entity.h>
#include <SDL.h>
#include <buffer.h>

class Player : public Entity{

    public: 

        bool up,down,left,right,dash,leftMouse,rightMouse;

        char status;

        char direction;

        double sleep, speed, hp, maxHp;

        Player(SDL_Renderer* _r, int x, int y, int w, int h) : Entity(_r,x,y,w,h){
            direction = 'L';
            up = false;
            down = false;
            left = false;
            right = false;
            speed = 70;
            team = 1;
            sleep = 0;
            status = ' ';
            maxHp = 0;
            hp = maxHp;
        }

        virtual void update(double mod);

        virtual void move(double mod);

        virtual void collided(Entity* _e);

        void keyDown(SDL_Scancode key);

        void keyUp(SDL_Scancode key);

        void click(SDL_MouseButtonEvent click);

        virtual void specialDown(int key);
        virtual void specialUp(int key);


};