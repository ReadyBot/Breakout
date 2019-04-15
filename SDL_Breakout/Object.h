#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>
#include <iostream>
#include <vector>
#include "ResourceManager.h"
#include "Collider.h"
#include "Input.h"

class Object{
public:

	Object();
	~Object();

	virtual void Draw();
	virtual void Update(double deltaTime){};


protected:

	float speed = 0;
	SDL_Rect coords = {0, 0, 0, 0};
	std::vector<SDL_Texture*> textures;
	SDL_Texture *texture;
	Input *input;
	Collider collider;

};

#endif