#pragma once

#include "Entity2D.h"
#define MAX_VELOCITY 10.0
#define VELOCITY_RATE_OF_CHANGE 9.0
#define TURNING_RATE_OF_CHANGE 270.0

class SpaceShip : public Entity2D
{
public:
	SpaceShip();
	~SpaceShip();

	void init();
	void init(float x_pos, float y_pos, float rot);
	void update(float dt);
	void render();

	void turn(bool key_a, bool key_d);
	void boost(bool active);
	void toggle_gun();
	int gun_type = 0;
	bool is_dead = true;

private:
	float is_boosting = false;
	int turn_dir = 0;
};

