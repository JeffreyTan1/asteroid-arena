#pragma once

#include "Entity2D.h"
#define ALIVE_TIME 10

class Drone : public Entity2D
{
public:
	Drone();
	~Drone();

	void init();
	void init(float x_pos, float y_pos, float rot);
	void update(float dt);
	void render();

	bool expired = false;
private:
	float time_alive = 0.0;
};

