#include <entity.h>

class Terrain : public Entity{

    public:

        Terrain(SDL_Renderer* _r,int x, int y, int w, int h) : Entity(_r,x,y,w,h){
            team = 0;
            pos.r = 130;
            pos.b = 12;
            pos.g = 41;
        }

};