#include "GameManager.h"

breaker::GameManager *breaker::GameManager::instance_;

breaker::GameManager::GameManager(){
	Init();
}


breaker::GameManager::~GameManager(){
	delete(input_);
	delete(resourceManager_);
	delete(time_);
	delete(statManager_);
}

void breaker::GameManager::DeleteObject(Object *obj){
	auto it = std::remove(gameObjects_.begin(), gameObjects_.end(), obj);
	if(it == gameObjects_.end()){
		std::cout << "ERROR: Did not find object to delete. GameManager" << std::endl;
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
	resourceManager_ = ResourceManager::Instance();
	time_ = Time::Instance();
	statManager_ = StatusManager::Instance();

	SDL_Color bgColor = {
		0, 0, 0, 255
	};

	if(!resourceManager_->CreateRenderer(Window::Instance()->GetWindow(), bgColor)){
		return;
	}
	
	CreatePlayer();
	CreateBall();
	CreateWalls();
	LoadLevel(currentLevel_);

	gameRunning_ = true;
	GameLoop();
}

void breaker::GameManager::CreatePlayer(){
	SDL_Rect coords = { 0, 0, 0, 0 };
	coords.w = playerWidth_;
	coords.h = playerHeight_;
	coords.x = Window_Width / 2 - coords.w / 2;
	coords.y = Window_Height - (coords.h * 8);
	player_ = new Player(coords, "paddle");
	gameObjects_.push_back(player_);
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
			coords = { -5, 0, 10, Window_Height };
			break;
		case 1:
			//Right Wall
			coords = { Window_Width - 5, 0, 10, Window_Height };
			break;
		case 2:
			//Top Wall
			coords = { 0, -5, Window_Width, 10 };
			break;
		case 3:
			//Bottom Wall
			coords = { 0, Window_Height - 5, Window_Width, 10 };
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
	if(hp > 0)
		bricksLeft_++;
}


void breaker::GameManager::CreateLevel(){
	for(int i = 0; i < levelStructure_.size(); i++){
		for(int j = 0; j < levelStructure_.at(i).size(); j++){
			if(levelStructure_.at(i).at(j) == 0)
				continue;
			int x = j * brickWidth_;
			int y = i * brickHeight_ + (brickHeight_ * 2);
			CreateBrick(x, y, levelStructure_.at(i).at(j));
		}
	}
}

void breaker::GameManager::LoadLevel(int levelIndex){
	ClearLevel();

	std::string lvl = "res/levels/level_" + std::to_string(levelIndex) + ".lvl";

	std::ifstream lvlFile(lvl);
	if(!lvlFile){
		std::cout << "Error: level file not found -> " << lvl << std::endl;
		if(levelIndex != 1){
			LoadLevel(1);  //If levelfile is not found and levelindex is not 1, start from level 1
		}
		return;
	}

	std::string lvlLine;
	while(!lvlFile.eof()){
		std::vector<int> brickRow;
		getline(lvlFile, lvlLine);
		for(int i = 0; i <= 9; i++){
			if(isdigit(lvlLine.at(i))){
				brickRow.push_back(lvlLine.at(i) - '0');
			} else if(lvlLine.at(i) == 'x'){
				brickRow.push_back(-1);
			}
		}
		levelStructure_.push_back(brickRow);
	}
	lvlFile.close();
	CreateLevel();
}

void breaker::GameManager::ClearLevel(){
	//Delete remaining bricks
	std::for_each(gameObjects_.rbegin(), gameObjects_.rend(), [this](Object *obj){
		if(dynamic_cast<Brick*>(obj)){
			DeleteObject(obj);
		}
	});
	//Clear levelStructure_ to have a clean vector to create a new level on
	std::for_each(levelStructure_.begin(), levelStructure_.end(), [this](std::vector<int> vec){
		vec.clear();
	});
	levelStructure_.clear();
}

void breaker::GameManager::GameLoop(){
	while(gameRunning_){

		time_->UpdateDeltaTime();
		input_->Update();
		if(input_->GetKeyDown(SDL_SCANCODE_ESCAPE)){
			gameRunning_ = false;
			break;
		}

		//TODO: Possibility to press the X to close program

		if(statManager_->GetRespawnBall()){
			RespawnBall();
			statManager_->RespawnBall(false);
		}

		if(statManager_->GetPlayerHp() > 0){
			//Check for collitions
			std::for_each(std::execution::par, gameObjects_.begin(), gameObjects_.end(), [this](Object *obj){
				if(ball_ != obj){
					if(ball_->CollidingWith(obj)){
						if(dynamic_cast<Player*>(obj)){
							ball_->CollidingWithPlayer();
						} else{
							obj->SetCollidingWith(ball_);
						}
					}
				}
			});
		}

		//
		std::for_each(gameObjects_.begin(), gameObjects_.end(), [this](Object *obj){
			if(statManager_->GetPlayerHp() > 0){
				obj->Update();
				//Remove bricks that has 0 hp
				if(obj->GetIfDelete()){
					bricksLeft_--;
					DeleteObject(obj);
				} else{
					obj->Draw();
				}
			}
		});

		if(bricksLeft_ <= 0){
			currentLevel_++; //Level overflow is checked when the new level is loaded
			RespawnBall();
			LoadLevel(currentLevel_);
		}

		resourceManager_->RefreshRenderer();

	}
}
