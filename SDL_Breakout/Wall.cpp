#include "Wall.h"



breaker::Wall::Wall(SDL_Rect coords){
	Object::coords = coords;
	collider = new Collider(coords);
	//std::cout << "Wall created" << std::endl;
}

breaker::Wall::~Wall(){}


void breaker::Wall::Update(){
	UpdateColliderPos();
	Object::Update();
}


void breaker::Wall::Draw(){
	SDL_RenderCopy(ResourceManager::Instance()->GetRenderer(), texture, nullptr, &coords);
}



