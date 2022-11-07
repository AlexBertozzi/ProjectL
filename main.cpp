#include <iostream>
#include <SDL.h>

#include "game.h"

const int SCREENWIDTH = 1280;
const int SCREENHEIGHT = 768;

int main(int argc, char**){

	SDL_Window* _window = NULL;

	SDL_Surface* _surface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}else{

		_window = SDL_CreateWindow("Project L", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN);

		if(_window == NULL){
			std::cout<<"SDL_CreateWindow Error: could not load window"<<std::endl;
		}else{

			_surface = SDL_GetWindowSurface(_window);

			SDL_Event event; 

			Game game = Game(_surface);

			do{

				SDL_FillRect(_surface, NULL, SDL_MapRGBA(_surface->format, 0,0,0,255));

				SDL_UpdateWindowSurface(_window);
				game.loop();

				SDL_PollEvent(&event);
			}while(event.type != SDL_QUIT);

		}
	}
	SDL_Quit();
	return 0;
}