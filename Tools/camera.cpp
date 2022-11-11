#include <camera.h>

extern const int SCREENWIDTH;
extern const int SCREENHEIGHT;

void Camera::update(){
    modX = _following->pos.fx - (SCREENWIDTH/2);

    if(modX< 0) modX= 0;
    if(modX> maxX) modX = maxX;

    modY = _following->pos.fy - (SCREENHEIGHT/2);

    if(modY< 0) modY=0;
    if(modY> maxY) modY = maxY;
}