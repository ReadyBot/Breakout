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
		int GetPlayerHp() const{ return playerHp_; }
		int GetScore() const{ return score_; }

		void RespawnBall(bool respawnBall){ respawnBall_ = respawnBall; }
		void IncrementScore(int count){
			score_ += count;
			std::cout << "Score: " << score_ << std::endl;
		}
		void DamagePlayer(){
			playerHp_ -= 1;
			std::cout << "Player hp left: " << playerHp_ << std::endl;
		}

	private:

		static StatusManager *instance_;

		bool respawnBall_ = false;
		int playerHp_ = 3;
		int score_ = 0;

	};
}

#endif