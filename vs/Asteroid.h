#pragma once

#include "Entity2D.h"

class Asteroid : public Entity2D
{
public:
	Asteroid();
	~Asteroid();

	void init();
	void init(float x_pos, float y_pos, float rot);
	void init(float x_pos, float y_pos, float rot, float vel, float scale_x, float scale_y, float is_split);
	void update(float dt);
	void render();
	int health = 0;
	bool inside_walls = false;
	bool is_split = false;
private:
	int type = 0;
	float rot_rate = 0.0;
	int rot_dir = 0;
};

