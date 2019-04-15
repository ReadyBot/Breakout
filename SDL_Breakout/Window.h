#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <string>

class Window{
public:
	static Window* Instance(){
		if(instance_ == nullptr)
			throw "No window created!";
		return instance_;
	}

	static Window* Instance(std::string title, int width, int height){
		if(instance_ == nullptr)
			instance_ = new Window(title, width, height);
		return instance_;
	}

	Window(std::string title, int width, int height);
	~Window();

	SDL_Window *GetWindow(){ return window_; };

	
private:
	
	void Init();
	SDL_Window* window_ = nullptr;

	std::string title_;
	int height_, width_;

	static Window* instance_;

};

#endif