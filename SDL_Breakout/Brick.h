#ifndef BRICK_H
#define BRICK_H

#include "Object.h"

namespace breaker{
	class Brick : public Object{
	public:

		Brick(SDL_Rect coords, std::string texturePath, int hp);
		~Brick();

		virtual void Update() override;
		virtual void Draw() override;

		bool SurvivesHit(){ return hp_ > 1; }

	private:

		void TakeDamage();

		bool hasCollided_ = false;
		std::string textureName_, texturePath_;
		int hp_;

	};
}

#endif