#include "Input.h"


Input *Input::instance_;

Input::Input(){
	keys = SDL_GetKeyboardState(&keyCount);
	oldKeys = std::unique_ptr<Uint8>(new Uint8[keyCount]);
}


Input::~Input(){}

void Input::Update(){
	
	mOldButtons = mButtons;
	memcpy(oldKeys.get(), keys, keyCount * sizeof(Uint8));

	SDL_PumpEvents();
	mButtons = SDL_GetRelativeMouseState(&mouseX, &mouseY);

}

