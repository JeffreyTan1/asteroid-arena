#pragma once

#include "Entity2D.h"

class Missile : public Entity2D
{
public:
	Missile();
	~Missile();

	void init();
	void init(float x_pos, float y_pos, float rot);
	void update(float dt);
	void render();

private:

};

