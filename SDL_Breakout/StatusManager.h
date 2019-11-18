#ifndef STATUSMANAGER_H
#define STATUSMANAGER_H

#include <iostream>

namespace breaker{
	class StatusManager{
	public:

		static StatusManager* Instance(){
			if(instance_ == nullptr)
				instance_ = new StatusManager();
			return instance_;
		}

		StatusManager();
		~StatusManager();

		bool GetRespawnBall() const{ return respawnBall_; }
		bool IsGamePaused() const{ return gamePaused_; }
		int GetPlayerHp() const{ return playerHp_; }
		int GetScore() const{ return score_; }

		void PauseGame(bool pause){
			gamePaused_ = pause;
			if(gamePaused_)
				std::cout << "Game Paused" << std::endl;
			else
				std::cout << "Game Unpaused" << std::endl;
		}
		void RespawnBall(bool respawnBall){ respawnBall_ = respawnBall; }
		void IncrementScore(int count){
			score_ += count;
			std::cout << "Score: " << score_ << std::endl;
		}
		void DamagePlayer(){
			playerHp_ -= 1;
			std::cout << "Player hp left: " << playerHp_ << std::endl;
			if(playerHp_ == 0)
				std::cout << "Game Over!\n" << "Total Score: " << score_ << std::endl;
		}

	private:

		static StatusManager *instance_;

		bool gamePaused_ = true;
		bool respawnBall_ = false;
		int playerHp_ = 3;
		int score_ = 0;

	};
}

#endif