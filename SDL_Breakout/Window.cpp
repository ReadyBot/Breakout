#include "Window.h"

Window *Window::instance_;

Window::Window(std::string title, int width, int height):
	title_(title), width_(width), height_(height){
	Init();
}

Window::~Window(){}

void Window::Init(){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK); // | SDL_INIT_JOYSTICK
	// For alle mulige konfigurasjonsalternativer, se: http://goo.gl/8vDJN
	window_ = SDL_CreateWindow(
		title_.c_str(), // window title
		SDL_WINDOWPOS_UNDEFINED, // initial x position
		SDL_WINDOWPOS_UNDEFINED, // initial y position
		width_, // width, in pixels
		height_, // height, in pixels
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL // flags
	);

}
