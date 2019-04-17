#ifndef BALL_H
#define BALL_H

#include "Object.h"

namespace breaker{
	class Ball : public Object{
	public:

		Ball(SDL_Rect coords, std::string texturePath, Vector2 dir);
		~Ball();

		virtual void Update() override;
		virtual void Draw() override;


	private:


		Vector2 direction_;
		float ballSpeed_ = 3;
		float x_ = 0, y_ = 0;

		int tmp = 0;

	};
}

#endif