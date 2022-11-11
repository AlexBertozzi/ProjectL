#pragma once

#include <entity.h>

class Camera{

    public:

        double modX,modY;

        double maxX,maxY;

        Entity* _following;

        Camera(){

            _following = NULL;
            maxX = 0;
            maxY = 0;
            modX = 0;
            modY = 0;
        }

        Camera(Entity* _e, double maxFrameX, double maxFrameY){
            
            _following = _e;
            maxX = maxFrameX;
            maxY = maxFrameY;
            modX = 0;
            modY = 0;
        }

        void update();
};