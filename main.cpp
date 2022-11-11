#include <iostream>
#include <SDL.h>
#include <camera.h>
#include <game.h>

const int SCREENWIDTH = 1280;
const int SCREENHEIGHT = 768;

Game game;

Camera camera;

int main(int argc, char**){

	SDL_Window* _window = NULL;

	SDL_Renderer* _renderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}else{

		_window = SDL_CreateWindow("Project L", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN);

		_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

		if(_renderer == NULL){
			std::cout<<"SDL_CreateRenderer Error: could not load window"<<std::endl;
		}else{

			SDL_Event event; 

			game = Game(_renderer);

			do{

				game.loop(&event);

				SDL_PollEvent(&event);
			}while(event.type != SDL_QUIT && (event.key.keysym.scancode != SDL_SCANCODE_ESCAPE));

		}
	}
	SDL_Quit();
	return 0;
}