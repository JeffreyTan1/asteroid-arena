#pragma once

#include "Entity2D.h"

class SpaceShip : public Entity2D
{
public:
	SpaceShip();
	~SpaceShip();

	void init();
	void update(float dt);
	void render();

	void turn(bool clockwise);
	void forward();


private:
	float drag = 0.2;
	bool isBoosting = false;

};

