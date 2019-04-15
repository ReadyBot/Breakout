#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Input.h"
#include "Player.h"

class GameManager{
public:
	GameManager();
	~GameManager();



private:

	void CreatePlayer();
	void CreateBtick();
	void GameLoop();
	void LoadLevel(int levelIndex);




};

#endif