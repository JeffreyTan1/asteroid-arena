#include "Drone.h"

Drone::Drone() {
}

Drone::~Drone() {
}

void Drone::init() {
}

void Drone::init(float x_pos, float y_pos, float rot) {
    transform.rotation = rot;
    transform.position.x = x_pos;
    transform.position.y = y_pos;
    transform.scale.x = 0.2;
    transform.scale.y = 0.2;
    circle.radius = 1.0;
}

void Drone::update(float dt) {
    // Destroy itself after some time has elapsed
    time_alive += dt;
    if (time_alive > ALIVE_TIME) {
        expired = true;
    }
}

void Drone::render() {

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(transform.position.x, transform.position.y, 0.0);
    glRotatef(transform.rotation, 0.0, 0.0, 1.0);
    glScalef(transform.scale.x, transform.scale.y, 0.0);

    glBegin(GL_POLYGON);
    glColor3f(214.0 / 255.0, 93.0 / 255.0, 177.0 / 255.0);
    glVertex3f(0.7, 0.0, 0.0);
    glVertex3f(0.5, 0.7, 0.0);
    glVertex3f(-0.5, 0.7, 0.0);
    glVertex3f(-0.7, 0.0, 0.0);
    glVertex3f(-0.5, -0.7, 0.0);
    glVertex3f(0.5, -0.7, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(255.0 / 255.0, 199.0 / 255.0, 95.0 / 255.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(0.6, 1.0, 0.0);
    glVertex3f(-0.6, 1.0, 0.0);
    glVertex3f(-1.0, 0.0, 0.0);
    glVertex3f(-0.6, -1.0, 0.0);
    glVertex3f(0.6, -1.0, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(255.0 / 255.0, 150.0 / 255.0, 113.0 / 255.0);
    glVertex3f(-0.2, 1.0, 0.0);
    glVertex3f(0.2, 1.0, 0.0);
    glVertex3f(-0.2, 1.5, 0.0);
    glVertex3f(0.2, 1.5, 0.0);
    glEnd();

    glPopMatrix();
}