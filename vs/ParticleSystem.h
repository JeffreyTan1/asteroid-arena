#pragma once

#include "Entity2D.h"

#define NUM_PARTICLES 40
#define ALIVE_TIME 0.7

typedef struct {
	vec2f_t position;
	vec2f_t direction;
	float velocity;
} particle;

class ParticleSystem : public Entity2D
{
public:
	ParticleSystem();
	~ParticleSystem();

	void init();
	void init(float x_pos, float y_pos, float rot);
	void init(float x_pos, float y_pos, float rot, float scale_x, float scale_y);
	void update(float dt);
	void render();

	bool expired = false;
private:
	particle particles[NUM_PARTICLES] = {};
	float time_alive = 0.0;
};

