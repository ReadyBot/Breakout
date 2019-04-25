#ifndef TIME_H
#define TIME_H

/*
	The Time class is used to keep track of delatTime. DeltaTime is a 'double' variable
	that tell the time between each frame. If you have 1 fps (1 frame per second) deltaTime
	will be 1000 ms (or as we have it 1 second). If you have 100 fps deltaTime will be 10 ms (0.1 s).
	DeltaTime is used to make movements smooth and the same speed independent from framerate.
*/

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