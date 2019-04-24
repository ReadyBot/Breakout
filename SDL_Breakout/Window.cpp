#include "Window.h"

breaker::Window *breaker::Window::instance_;

breaker::Window::Window(std::string title):
	title_(title){
	Init();
}

breaker::Window::~Window(){}

void breaker::Window::Init(){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK); // | SDL_INIT_JOYSTICK
	//TTF_Init();
	// For alle mulige konfigurasjonsalternativer, se: http://goo.gl/8vDJN
	window_ = SDL_CreateWindow(
		title_.c_str(), // window title
		SDL_WINDOWPOS_UNDEFINED, // initial x position
		SDL_WINDOWPOS_UNDEFINED, // initial y position
		Window_Width, // width, in pixels
		Window_Height, // height, in pixels
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL // flags
	);

}
