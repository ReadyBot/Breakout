#ifndef WALL_H
#define WALL_H

#include "Object.h"

namespace breaker{
	class Wall : public Object{
	public:

		Wall(SDL_Rect coords);
		~Wall();

		virtual void Update() override;
		virtual void Draw() override;

	};
}

#endif