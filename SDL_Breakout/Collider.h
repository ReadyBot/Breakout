#pragma once
class Collider{
public:
	
	Collider(int x, int y, int w, int h);
	~Collider();

	static bool Colliding(Collider col1, Collider col2);

	void Update(int x, int y);
	void Change(int w, int h);

	int x_, y_, w_, h_;


};

