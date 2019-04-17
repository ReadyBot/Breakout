#include "Brick.h"
#include "GameManager.h"



breaker::Brick::Brick(SDL_Rect coords, std::string texturePath, int hp) : hp_(hp), texturePath_(texturePath){
	textureName_ = texturePath_ + std::to_string(hp_);
	texture = ResourceManager::Instance()->GetTexture(textureName_);
	Object::coords = coords;
	collider = new Collider(coords);
	std::cout << coords.x << " " << coords.y << " " << coords.w << " " << coords.h << std::endl;
	std::cout << "Brick created" << std::endl;
}

breaker::Brick::~Brick(){}

void breaker::Brick::Update(){
	UpdateColliderPos();

	if(collidingObject != nullptr){
		hasCollided_ = true;
	}
	if(hasCollided_ && collidingObject == nullptr){
		hasCollided_ = false;
		TakeDamage();
	}

	Object::Update();
	//TODO: If hit, reduce hp and get new texture based on hp
}


void breaker::Brick::Draw(){
	if(hp_ == 0){
		return;
	}
	SDL_RenderCopy(ResourceManager::Instance()->GetRenderer(), texture, nullptr, &coords);
	SDL_RenderDrawRect(ResourceManager::Instance()->GetRenderer(), &coords); //Drawing frame of rect
}

void breaker::Brick::TakeDamage(){
	hp_ -= 1;
	if(hp_ == 0){
		deleteReady = true;
		StatusManager::Instance()->IncrementScore(1000);
		return;
	}
	StatusManager::Instance()->IncrementScore(100);
	textureName_ = texturePath_ + std::to_string(hp_);
	texture = ResourceManager::Instance()->GetTexture(textureName_);
}


