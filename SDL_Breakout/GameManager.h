#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <iostream>
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <fstream>

#include "StatusManager.h"
#include "Window.h"
#include "Input.h"
#include "Player.h"
#include "Brick.h"
#include "Ball.h"
#include "Wall.h"
#include "DeathWall.h"
#include "Vector2.h"

namespace breaker{
	class GameManager{
	public:

		static GameManager* Instance(){
			if(instance_ == nullptr){
				instance_ = new GameManager();
			}
			return instance_;
		}

		GameManager();
		~GameManager();

		void DeleteObject(Object *obj);
		void RespawnBall();

	private:

		static GameManager *instance_;

		void Init();
		void CreatePlayer();
		void CreateBall();
		void CreateWalls();
		void CreateBrick(int x, int y, int hp);
		void CreateLevel();
		void LoadLevel(int levelIndex);
		void GameLoop();


		std::vector<Object*> gameObjects_;
		StatusManager *statMan_;
		Input *input_;
		ResourceManager *resManag_;
		Time *time_;

		int score_ = 0;

		std::vector<std::vector<int>> lvlStruct;

		float playerWidth_ = Window_Width / 6;
		float playerHeight_ = Window_Height / 40;
		float brickWidth_ = Window_Width / 10;
		float brickHeight_ = Window_Height / 20;
		float ballSize_ = Window_Width / 50;

		Object *ball_;

		bool gameRunning_;

	};
}

#endif