#include "Ball.h"



breaker::Ball::Ball(SDL_Rect coords, std::string texturePath, Vector2 dir) : Object(), direction_(dir) {
	texture = ResourceManager::Instance()->GetTexture(texturePath);
	speed = ballSpeed_;
	Object::coords = coords;
	x_ = coords.x;
	y_ = coords.y;
	collider = new Collider(coords);
	std::cout << "Ball created" << std::endl;
}


breaker::Ball::~Ball(){}


void breaker::Ball::Update(){

	UpdateColliderPos();
	if(collidingObject != nullptr){
		SDL_Rect other = collidingObject->GetCoords();
		tmp++;
		//std::cout << "Colliding: " << tmp << std::endl;

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

	x_ += speed * 50 * Time::Instance()->DeltaTime() * direction_.x;
	y_ += speed * 50 * Time::Instance()->DeltaTime() * direction_.y;

	coords.x = static_cast<int>(x_);
	coords.y = static_cast<int>(y_);

	Object::Update();
}

void breaker::Ball::Draw(){
	SDL_RenderCopy(ResourceManager::Instance()->GetRenderer(), texture, nullptr, &coords);
}


