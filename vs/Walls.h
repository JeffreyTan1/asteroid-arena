#pragma once

#include "Entity2D.h"

class Walls : public Entity2D
{
public:
	Walls();
	~Walls();

	void init(float x_pos, float y_pos, float rot);
	void init();
	void update(float dt);
	void render();

	void warn();
	void safe();

	line2d_t l_wall = { {0.0, 0.0}, {0.0, 0.0} };
	line2d_t r_wall = { {0.0, 0.0}, {0.0, 0.0} };
	line2d_t t_wall = { {0.0, 0.0}, {0.0, 0.0} };
	line2d_t b_wall = { {0.0, 0.0}, {0.0, 0.0} };

private:
	float r;
	float g;
	float b;
};

