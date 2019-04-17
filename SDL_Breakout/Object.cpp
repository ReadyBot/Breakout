#include "Object.h"


breaker::Object::Object(){
	input = Input::Instance();
	//std::cout << "Object created" << std::endl;
}


breaker::Object::~Object(){
	delete(collider);
	//std::cout << "Deleting Object" << std::endl;
}

bool breaker::Object::CollidingWith(Object *obj){
	//collidingObject = nullptr;
	if(collider->Colliding(obj->GetCollider())){
		collidingObject = obj;
		return true;
	}
	return false;
}

void breaker::Object::CreteCollider(SDL_Rect coords){
	collider = new Collider(coords);
}

void breaker::Object::UpdateColliderPos(){
	//std::cout << coords.x << " : " << coords.y << std::endl;
	collider->Update(coords);
}

