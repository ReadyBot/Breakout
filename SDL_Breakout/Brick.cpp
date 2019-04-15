#include "Brick.h"



Brick::Brick(SDL_Rect coords, SDL_Texture * texture_){
	texture = texture_;
	Object::coords = coords;
	Object::coords.y = 100;
	Object::coords.x = 200;
	std::cout << "Brick created" << std::endl;
}

Brick::~Brick(){}

void Brick::Update(double deltaTime){
	
}


void Brick::Draw(){
	SDL_RenderCopy(ResourceManager::Instance()->GetRenderer(), texture, nullptr, &coords);
}


