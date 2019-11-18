#include "Ball.h"



breaker::Ball::Ball(SDL_Rect coords, std::string texturePath, Vector2 dir) : Object(), direction_(dir), x_(coords.x), y_(coords.y) {
	texture = ResourceManager::Instance()->GetTexture(texturePath);
	speed = ballSpeed_;
	Object::coords = coords;
	collider = new Collider(coords);
	//std::cout << "Ball created" << std::endl;
}


breaker::Ball::~Ball(){}


void breaker::Ball::Update(){

	UpdateColliderPos();
	if(collidingObject != nullptr){
		SDL_Rect other = collidingObject->GetCoords();

		if(collidingWithPlayer_){
			//Hitting left 1/3 of the paddle
			if(coords.x + coords.w < other.x + (other.w / 3)){
				direction_.x = -1;
			}
			//Hitting right 1/3 of the paddle
			if(coords.x > other.x + ((other.w / 3) * 2)){
				direction_.x = 1;
			}
			direction_.y = -1;
			collidingWithPlayer_ = false;
		} else {
			if(coords.x < other.x){
				direction_.x = -1;
			}
			if(coords.x + coords.w > other.x + other.w){
				direction_.x = 1;
			}
			if(coords.y < other.y){
				direction_.y = -1;
			}
			if(coords.y + coords.h > other.y + other.h){
				direction_.y = 1;
			}
		}
	}

	x_ += speed * 50 * Time::Instance()->DeltaTime() * direction_.x;
	y_ += speed * 50 * Time::Instance()->DeltaTime() * direction_.y;

	coords.x = static_cast<int>(x_);
	coords.y = static_cast<int>(y_);

	Object::Update();
}

void breaker::Ball::Draw(){
	SDL_RenderCopy(ResourceManager::Instance()->GetRenderer(), texture, nullptr, &coords);
}




