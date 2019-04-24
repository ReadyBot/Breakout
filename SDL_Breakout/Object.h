#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>
#include <iostream>
#include <vector>
#include "ResourceManager.h"
#include "Collider.h"
#include "Input.h"
#include "Time.h"
#include "Vector2.h"
#include "StatusManager.h"

class GameManager;

namespace breaker{
	class Object{
	public:

		Object();
		~Object();

		virtual void Draw(){}
		virtual void Update(){ collidingObject = nullptr; }
		bool CollidingWith(Object *obj);
		void SetCollidingWith(Object *obj){ collidingObject = obj; }
		void CreteCollider(SDL_Rect coords);
		SDL_Rect GetCoords() const{ return coords; }

		int GetIfDelete(){ return deleteReady; }

		Collider *GetCollider() const{ return collider; }

		void CollidingWithPlayer(){ collidingWithPlayer_ = true; }

	protected:

		void UpdateColliderPos();

		GameManager *gameManager;

		float speed = 0;
		Object *collidingObject = nullptr;
		SDL_Rect coords = { 0, 0, 0, 0 };
		std::vector<SDL_Texture*> textures;
		SDL_Texture *texture;
		Input *input;
		Collider *collider;
		bool deleteReady = false;
		bool collidingWithPlayer_ = false;


	};
}

#endif