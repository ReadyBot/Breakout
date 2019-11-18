#ifndef DEATHWALL_H
#define DEATHWALL_H

/*
	Deathwall is, if not guessed, the collider under the player
	that detects a "death" when the ball collides with it.
*/

#include "Object.h"

namespace breaker{
	class DeathWall : public Object{
	public:

		DeathWall(SDL_Rect coords);
		~DeathWall();

		virtual void Update() override;
		virtual void Draw() override;

	private:

		bool hasCollided_ = false;

	};
}

#endif