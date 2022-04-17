#pragma once

#include "Entity2D.h"

class Bullet : public Entity2D
{
public:
	Bullet();
	~Bullet();

	void init();
	void update(float dt);
	void render();
private:

};

