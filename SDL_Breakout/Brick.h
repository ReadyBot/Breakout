#ifndef BRICK_H
#define BRICK_H

#include "Object.h"

class Brick : public Object{
public:

	Brick(SDL_Rect coords, SDL_Texture *texture_);
	~Brick();

	virtual void Update(double deltaTime) override;
	virtual void Draw() override;

	bool SurvivesHit(){ return hp_ > 1; }

private:

	int hp_;

};

#endif