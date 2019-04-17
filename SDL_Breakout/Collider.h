#ifndef COLLIDER_H
#define COLLIDER_H

#include "SDL_Rect.h"
#include <iostream>

namespace breaker{
	class Collider{
	public:

		Collider(float x, float y, float w, float h);
		Collider(SDL_Rect rect);
		~Collider();

		bool Colliding(Collider *other);

		void Update(SDL_Rect coords);

		float x_, y_, w_, h_;

	};
}

#endif