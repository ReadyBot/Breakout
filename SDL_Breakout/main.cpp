
#include <iostream>

#include "GameManager.h"
#include "Window.h"



int main(int argc, char* argv[]){

	SDL_Window *window = breaker::Window::Instance("SDL_Breakout")->GetWindow();
	breaker::GameManager *gManager = breaker::GameManager::Instance();

	delete(gManager);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}
