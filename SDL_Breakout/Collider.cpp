#include "Collider.h"


Collider::Collider(int x, int y, int w, int h) : x_(x), y_(y), w_(w), h_(h){
	
}

Collider::~Collider(){}

bool Collider::Colliding(Collider col1, Collider col2){
	if(col1.x_ > col2.x_ && col1.y_ > col2.y_ &&
		col1.x_ + col1.w_ < col2.x_ + col2.w_ && col1.y_ + col1.h_ < col2.y_ + col2.h_)
		return true;
	return false;
}

void Collider::Update(int x, int y){
	x_ = x;
	y_ = y;
}

void Collider::Change(int w, int h){
	w_ = w;
	h_ = h;
}



