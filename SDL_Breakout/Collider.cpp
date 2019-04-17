#include "Collider.h"


breaker::Collider::Collider(float x, float y, float w, float h) : x_(x), y_(y), w_(w), h_(h){
	//std::cout << "x: " << x_ << " y: " << y_ << " w: " << w_ << " h: " << h_ << std::endl;
}

breaker::Collider::Collider(SDL_Rect rect){
	Collider(rect.x, rect.y, rect.w, rect.h);
}

breaker::Collider::~Collider(){}

//AABB Collition format from:
//https://tutorialedge.net/gamedev/aabb-collision-detection-tutorial/
bool breaker::Collider::Colliding(Collider *other){

	//std::cout << (x_ < other->x_ + other->w_) << " -> " << x_ << " : " << other->x_ << " w: " << other->w_ << std::endl;

	if(x_ < other->x_ + other->w_ &&
		x_ + w_ > other->x_ &&
		y_ < other->y_ + other->h_ &&
		y_ + h_ > other->y_){
		return true;
	}
	return false;
}

void breaker::Collider::Update(SDL_Rect coords){
	x_ = coords.x;
	y_ = coords.y;
	w_ = coords.w;
	h_ = coords.h;
}



