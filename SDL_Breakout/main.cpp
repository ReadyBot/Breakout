
#include <iostream>

#include "GameManager.h"
#include "Window.h"



int main(int argc, char* argv[]){

	SDL_Window *window = breaker::Window::Instance("SDL_Breakout")->GetWindow();
	breaker::GameManager *manager = breaker::GameManager::Instance();

	delete(manager);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	return EXIT_SUCCESS;
}
