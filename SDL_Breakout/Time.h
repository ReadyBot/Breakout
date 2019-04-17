#ifndef TIME_H
#define TIME_H

#include <SDL.h>
#include <iostream>

namespace breaker{
	class Time{
	public:

		static Time* Instance(){
			if(instance_ == nullptr)
				instance_ = new Time();
			return instance_;
		}

		Time();
		~Time();

		void UpdateDeltaTime();
		double DeltaTime(){ return deltaTime; }


	private:
		static Time *instance_;

		Uint64 NOW = SDL_GetPerformanceCounter();
		Uint64 LAST = 0;
		double deltaTime = 0, fps = 0, fpsTimer = 0;

	};
}

#endif