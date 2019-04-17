#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

namespace breaker{
	class Player : public Object{
	public:

		Player(SDL_Rect coords, std::string texturePath);
		~Player();

		virtual void Update() override;
		virtual void Draw() override;


	private:

		float playerSpeed_ = 3;
		float sprintSpeed_ = 5;
		float x_ = 0, y_ = 0;

	};
}

#endif