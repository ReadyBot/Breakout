#include "GameManager.h"

breaker::GameManager *breaker::GameManager::instance_;

breaker::GameManager::GameManager(){
	Init();
}


breaker::GameManager::~GameManager(){
	delete(input_);
	delete(resManag_);
	delete(time_);
}

void breaker::GameManager::DeleteObject(Object *obj){
	auto it = std::remove(gameObjects_.begin(), gameObjects_.end(), obj);
	if(it == gameObjects_.end()){
		std::cout << "ERROR: Did not find object to delete. GameManager->19" << std::endl;
		return;
	}
	gameObjects_.erase(it, gameObjects_.end());
	delete(obj);
}

void breaker::GameManager::RespawnBall(){
	DeleteObject(ball_);
	CreateBall();
}


void breaker::GameManager::Init(){

	input_ = Input::Instance();
	resManag_ = ResourceManager::Instance();
	time_ = Time::Instance();
	statMan_ = StatusManager::Instance();

	SDL_Color bgColor = {
		0, 0, 0, 255
	};

	if(!resManag_->CreateRenderer(Window::Instance()->GetWindow(), bgColor)){
		SDL_DestroyWindow(Window::Instance()->GetWindow());
		SDL_Quit();
		return;
	}
	
	CreatePlayer();
	CreateBall();
	CreateWalls();
	LoadLevel(1);

	gameRunning_ = true;
	GameLoop();
}

void breaker::GameManager::CreatePlayer(){
	SDL_Rect coords = { 0, 0, 0, 0 };
	coords.w = playerWidth_;
	coords.h = playerHeight_;
	coords.x = Window_Width / 2 - coords.w / 2;
	coords.y = Window_Height - (coords.h * 8);
	Object *obj = new Player(coords, "brick_0");
	gameObjects_.push_back(obj);
}


void breaker::GameManager::CreateBall(){
	SDL_Rect coords = { 0, 0, 0, 0 };
	coords.w = ballSize_;
	coords.h = ballSize_;
	coords.x = Window_Width / 2 - coords.w / 2;
	coords.y = Window_Height - (playerHeight_ * 10);
	Vector2 dir = { 1, -1 };
	ball_ = new Ball(coords, "ball", dir);
	gameObjects_.push_back(ball_);
}

void breaker::GameManager::CreateWalls(){
	for(int i = 0; i < 4; i++){
		SDL_Rect coords = { 0, 0, 0, 0 };
		switch(i){
		case 0:
			//Left Wall
			coords = { 0, 0, 10, Window_Height };
			break;
		case 1:
			//Right Wall
			coords = { Window_Width - 10, 0, 10, Window_Height };
			break;
		case 2:
			//Top Wall
			coords = { 0, 0, Window_Width, 10 };
			break;
		case 3:
			//Bottom Wall
			coords = { 0, Window_Height - 10, Window_Width, 10 };
			DeathWall *dWall = new DeathWall(coords);
			gameObjects_.push_back(dWall);
			return;
		}
		Wall *wall = new Wall(coords);
		gameObjects_.push_back(wall);
	}
}


void breaker::GameManager::CreateBrick(int x, int y, int hp){
	SDL_Rect coords = { 0, 0, 0, 0 };
	coords.x = x;
	coords.y = y;
	coords.w = brickWidth_;
	coords.h = brickHeight_;
	std::string textureString = "brick_";
	Object *obj = new Brick(coords, textureString, hp);
	gameObjects_.push_back(obj);
}


void breaker::GameManager::CreateLevel(){
	for(int i = 0; i < lvlStruct.size(); i++){
		for(int j = 0; j < lvlStruct.at(i).size(); j++){
			if(lvlStruct.at(i).at(j) == 0)
				continue;
			int x = j * brickWidth_; //((Window_Width - 10 * brickWidth_) / 2)
			int y = i * brickHeight_ + brickHeight_;
			CreateBrick(x, y, lvlStruct.at(i).at(j));
		}
	}
}

void breaker::GameManager::LoadLevel(int levelIndex){

	std::vector<int> r = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	std::vector<int> t = { 0, 1, 2, 3, 1, 2, 3, 1, 2, 0 };
	std::vector<int> y = { 0, 3, 2, 1, 3, 2, 1, 3, 2, 0 };
	lvlStruct.push_back(r);
	lvlStruct.push_back(t);
	lvlStruct.push_back(y);
	CreateLevel();
	return;

	std::string lvl = "res/levels/level_" + std::to_string(levelIndex) + ".lvl";

	std::ifstream lvlFile(lvl);
	if(!lvlFile){
		std::cout << "Error: level file not found -> " << lvl << std::endl;
		return;
	}
	
	for(int row = 0; row < 5; row++){  // stop loops if nothing to read
		std::vector<int> vec;
		for(int column = 0; column < 9; column++){
			int i = 0;
			lvlFile >> i;
			vec.push_back(i);
		}
		lvlStruct.push_back(vec);
	}
	CreateLevel();
	return;

	
	for(int i = 1; i < 9; i++){
		for(int j = 1; j < 5; j++){
			int x = i * brickWidth_; //((Window_Width - 10 * brickWidth_) / 2)
			int y = j * brickHeight_ + brickHeight_;
			CreateBrick(x, y, 3);
		}
	}
}

void breaker::GameManager::GameLoop(){
	while(gameRunning_){
		
		time_->UpdateDeltaTime();
		input_->Update();
		if(input_->GetKeyDown(SDL_SCANCODE_ESCAPE)){
			gameRunning_ = false;
			break;
		}

		if(statMan_->GetRespawnBall()){
			RespawnBall();
			statMan_->RespawnBall(false);
		}

		if(statMan_->GetPlayerHp() > 0){

			std::for_each(gameObjects_.begin(), gameObjects_.end(), [this](Object *obj){
				if(ball_ != obj){
					if(ball_->CollidingWith(obj)){
						obj->SetCollidingWith(ball_);
					}
				}
			});

			std::for_each(gameObjects_.begin(), gameObjects_.end(), [this](Object *obj){
				obj->Update();
				if(obj->GetIfDelete()){
					DeleteObject(obj);
				} else{
					obj->Draw();
				}
			});
		}

		resManag_->RefreshRenderer();

	}
}
