#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {
}

ParticleSystem::~ParticleSystem() {
}

void ParticleSystem::init() {
}

void ParticleSystem::init(float x_pos, float y_pos, float rot) {
}

void ParticleSystem::init(float x_pos, float y_pos, float rot, float scale_x, float scale_y) {
    transform.rotation = rot;
    transform.position.x = x_pos;
    transform.position.y = y_pos;
    transform.scale.x = scale_x;
    transform.scale.y = scale_y;

    for (int i = 0; i < NUM_PARTICLES; ++i) {
        int rand_deg = rand() % 360;
        float rand_rad = rand_deg * PI / 180.0;
        particles[i] = { {0.0, 0.0}, {(float) cos(rand_rad), (float) sin(rand_rad)}, (float) (rand() % 3) + 1};
    }
}

void ParticleSystem::update(float dt) {
    for (int i = 0; i < NUM_PARTICLES; ++i) {
        particles[i].position.x += particles[i].direction.x * particles[i].velocity * dt;
        particles[i].position.y += particles[i].direction.y * particles[i].velocity * dt;
    }

    // Destroy itself after some time has elapsed
    time_alive += dt;
    if (time_alive > ALIVE_TIME) {
        expired = true;
    }
}

void ParticleSystem::render() {

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(transform.position.x, transform.position.y, 0.0);
    glRotatef(transform.rotation, 0.0, 0.0, 1.0);
    glScalef(transform.scale.x, transform.scale.y, 0.0);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   

    glEnable(GL_POINT_SMOOTH);
    glPointSize(1.0);
    float opacity = ALIVE_TIME - time_alive < 0 ? 0 : (ALIVE_TIME - time_alive) / ALIVE_TIME;
    glEnable(GL_BLEND);

    glBegin(GL_POINTS);
    glColor4f(255.0 / 255.0, 255.0 / 255.0, 255.0 / 255.0, opacity);
    for (int i = 0; i < NUM_PARTICLES; ++i) {
        glVertex3f(particles[i].position.x, particles[i].position.y, 0.0);
    }
    glEnd();

    glDisable(GL_BLEND);
    glPopMatrix();
}