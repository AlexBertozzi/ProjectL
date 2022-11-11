#include <SDL.h>
#include <player.h>

class HUD{
    public:

        Player* _tracking;

        SDL_Renderer* _renderer;

        SDL_Rect hpPos;

        int hpLen;

        HUD(){
            _tracking = NULL;
            _renderer = NULL;

            hpLen = 200;

            hpPos.x = 10;
            hpPos.y = 10;
            hpPos.w = 150;
            hpPos.h = 25;
        }

        void show();
};