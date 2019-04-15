#pragma once
#include "Object.h"
class Ball : public Object{
public:

	Ball(SDL_Rect coords, SDL_Texture *texture_);
	~Ball();

	virtual void Update(double deltaTime) override;
	virtual void Draw() override;


private:



	float ballSpeed_ = 3;
	float x_ = 0, y_ = 0;

};

