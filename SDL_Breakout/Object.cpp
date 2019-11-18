#include "Object.h"


breaker::Object::Object(){
	input = Input::Instance();
}


breaker::Object::~Object(){
	delete(collider);
}

bool breaker::Object::CollidingWith(Object *obj){
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
	collider->Update(coords);
}

