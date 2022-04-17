#pragma once

#include "Entity2D.h"

class Bullet : public Entity2D
{
public:
	Bullet();
	~Bullet();

	void init();
	void init(float x_pos, float y_pos, float rot);
	void update(float dt);
	void render();
private:

};

