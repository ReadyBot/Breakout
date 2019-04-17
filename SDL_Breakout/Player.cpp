#include "Player.h"


breaker::Player::Player(SDL_Rect coords, std::string texturePath) : Object(){
	texture = ResourceManager::Instance()->GetTexture(texturePath);
	speed = playerSpeed_;
	Object::coords = coords;
	x_ = coords.x;
	y_ = coords.y;
	collider = new Collider(coords);
	std::cout << "Player created" << std::endl;
}

breaker::Player::~Player(){
	//std::cout << "Deleting from Player" << std::endl;
}


void breaker::Player::Update(){
	UpdateColliderPos();
	
	if(input->GetKey(SDL_SCANCODE_LSHIFT)){
		speed = sprintSpeed_;
	} else{
		speed = playerSpeed_;
	}

	if(input->GetKey(SDL_SCANCODE_RIGHT)){
		x_ += speed * 100 * Time::Instance()->DeltaTime();
	} else if(input->GetKey(SDL_SCANCODE_LEFT)){
		x_ -= speed *100 * Time::Instance()->DeltaTime();
	}/*
	if(input->GetKey(SDL_SCANCODE_DOWN) || input->GetKeyDown(SDL_SCANCODE_DOWN)){
		y_ += speed_ * 100 * deltaTime;
	} else if(input->GetKey(SDL_SCANCODE_UP) || input->GetKeyDown(SDL_SCANCODE_UP)){
		y_ -= speed_ * 100 * deltaTime;
	}*/
	coords.x = static_cast<int>(x_);
	coords.y = static_cast<int>(y_);
	//std::cout << "x: " << coords.x << " y: " << coords.y << std::endl;
	Object::Update();
}

void breaker::Player::Draw(){
	SDL_RenderCopy(ResourceManager::Instance()->GetRenderer(), texture, nullptr, &coords);
	//std::cout << "Drawing from Player" << std::endl;
}



