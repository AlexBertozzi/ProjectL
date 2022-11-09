#pragma once
#include <entity.h>
#include <SDL.h>
#include <buffer.h>

class Player : public Entity{

    public: 

        bool up,down,left,right,jump;

        char direction;

        Buffer buffer;

        double flySpeed,airborne,sleep,gravity,verticalSpeed, orizontalSpeed, maxVerticalSpeed, jumpHeight, orizontalMomentum;

        Player(SDL_Renderer* _r, int x, int y, int w, int h) : Entity(_r,x,y,w,h){
            direction = 'L';
            up = false;
            down = false;
            left = false;
            right = false;
            jump = false;
            airborne = 0;
            verticalSpeed = 0;
            orizontalSpeed = 50;
            maxVerticalSpeed = 100;
            flySpeed = 20;
            team = 1;
            jumpHeight = 100;
            gravity = 50;
            buffer.size = 10;
            buffer.index = 0;
            buffer.buffer = new int[buffer.size];
            sleep = 0;
            orizontalMomentum = 0;
        }

        void update(double mod);

        virtual void move(double mod);

        void collided(Entity* _e);

        void keyDown(SDL_Scancode key);

        void keyUp(SDL_Scancode key);

        bool checkBuffer(int size, int* toCheck);

        virtual bool special(int button);

        virtual void normal(int button);
};