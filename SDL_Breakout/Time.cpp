#include "Time.h"

breaker::Time *breaker::Time::instance_;

breaker::Time::Time(){}


breaker::Time::~Time(){}

void breaker::Time::UpdateDeltaTime(){
	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();

	deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
	deltaTime *= 0.001; //Convert from milli to seconds, because its a choice we did

	fpsTimer += deltaTime;
	if(deltaTime > 0.040){
		//Uncomment to show long frames in console
		//std::cout << "long frame: " << deltaTime << std::endl;
		deltaTime = 0;
	}
	fps++;
	if(fpsTimer >= 1){
		//Uncomment to show fps in console. Updated every seconds, not frame
		//std::cout << "fps: " << fps << std::endl;
		fps = 0;
		fpsTimer = 0;
	}
}

