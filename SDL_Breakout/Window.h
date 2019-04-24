#ifndef WINDOW_H
#define WINDOW_H

#define Window_Width 550
#define Window_Height 400

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

namespace breaker{
	class Window{
	public:
		static Window* Instance(){
			if(instance_ == nullptr)
				throw "No window created!";
			return instance_;
		}

		static Window* Instance(std::string title){
			if(instance_ == nullptr)
				instance_ = new Window(title);
			return instance_;
		}

		Window(std::string title);
		~Window();

		SDL_Window *GetWindow(){ return window_; };

		static float WindowWidth(){ return Window_Width; }
		static float WindowHeight(){ return Window_Height; }

	private:

		void Init();
		SDL_Window* window_ = nullptr;

		std::string title_;
		int height_, width_;

		static Window* instance_;

	};
}

#endif