#include "Input.h"


breaker::Input *breaker::Input::instance_;

breaker::Input::Input(){
	keys = SDL_GetKeyboardState(&keyCount);
	oldKeys = std::unique_ptr<Uint8>(new Uint8[keyCount]);
}


breaker::Input::~Input(){}

void breaker::Input::Update(){
	
	mOldButtons = mButtons;
	memcpy(oldKeys.get(), keys, keyCount * sizeof(Uint8));

	SDL_PumpEvents();
	mButtons = SDL_GetRelativeMouseState(&mouseX, &mouseY);

}

