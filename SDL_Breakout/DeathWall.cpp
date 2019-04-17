#include "DeathWall.h"
#include "GameManager.h"

breaker::DeathWall::DeathWall(SDL_Rect coords){
	Object::coords = coords;
	collider = new Collider(coords);
	std::cout << "DeathWall created" << std::endl;
}

breaker::DeathWall::~DeathWall(){}

void breaker::DeathWall::Update(){
	UpdateColliderPos();

	if(collidingObject != nullptr){
		hasCollided_ = true;
	}
	if(hasCollided_ && collidingObject == nullptr){
		hasCollided_ = false;
		StatusManager::Instance()->DamagePlayer();
		StatusManager::Instance()->RespawnBall(true);
	}

	Object::Update();
}

void breaker::DeathWall::Draw(){
	SDL_RenderCopy(ResourceManager::Instance()->GetRenderer(), texture, nullptr, &coords);
}
