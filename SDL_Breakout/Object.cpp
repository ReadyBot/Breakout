#include "Object.h"



Object::Object(){
	input = Input::Instance();
	std::cout << "Object created" << std::endl;
}


Object::~Object(){
	std::cout << "Deleting Object" << std::endl;
}

void Object::Draw(){
	//std::cout << "Drawign from Object" << std::endl;
}

