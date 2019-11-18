#include "Player.h"


breaker::Player::Player(SDL_Rect coords, std::string texturePath) : Object(), x_(coords.x), y_(coords.y){
	texture = ResourceManager::Instance()->GetTexture(texturePath);
	speed = playerSpeed_;
	Object::coords = coords;
	collider = new Collider(coords);
	//std::cout << "Player created" << std::endl;
}

breaker::Player::~Player(){
}


void breaker::Player::Update(){
	UpdateColliderPos();
	
	if(input->GetKey(SDL_SCANCODE_LSHIFT)){
		speed = sprintSpeed_;
	} else{
		speed = playerSpeed_;
	}

	//The player is not limited to the window,
	// and can move to the left and right as far as the player wants
	if(input->GetKey(SDL_SCANCODE_RIGHT)){
		x_ += speed * 100 * Time::Instance()->DeltaTime();
	} else if(input->GetKey(SDL_SCANCODE_LEFT)){
		x_ -= speed *100 * Time::Instance()->DeltaTime();
	}
	coords.x = static_cast<int>(x_);
	coords.y = static_cast<int>(y_);

	Object::Update();
}

void breaker::Player::Draw(){
	SDL_RenderCopy(ResourceManager::Instance()->GetRenderer(), texture, nullptr, &coords);
}



