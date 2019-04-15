#include "Ball.h"



Ball::Ball(SDL_Rect coords, SDL_Texture *texture_) : Object(){
	texture = texture_;
	speed = ballSpeed_;
	Object::coords = coords;
	x_ = coords.x;
	y_ = coords.y;
	std::cout << "Ball created" << std::endl;
}


Ball::~Ball(){}

void Ball::Update(double deltaTime){


	/*if(input->GetKey(SDL_SCANCODE_RIGHT)){
		x_ += speed * 100 * deltaTime;
	} else if(input->GetKey(SDL_SCANCODE_LEFT)){
		x_ -= speed * 100 * deltaTime;
	}
	if(input->GetKey(SDL_SCANCODE_DOWN) || input->GetKeyDown(SDL_SCANCODE_DOWN)){
		y_ += speed_ * 100 * deltaTime;
	} else if(input->GetKey(SDL_SCANCODE_UP) || input->GetKeyDown(SDL_SCANCODE_UP)){
		y_ -= speed_ * 100 * deltaTime;
	}*/
	coords.x = static_cast<int>(x_);
	coords.y = static_cast<int>(y_);
}

void Ball::Draw(){
	SDL_RenderCopy(ResourceManager::Instance()->GetRenderer(), texture, nullptr, &coords);
}


