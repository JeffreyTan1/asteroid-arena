#include "SpaceShip.h"
#include <iostream>

using std::cout;
using std::endl;


SpaceShip::SpaceShip() {
    r_val, g_val, b_val = 0.0;
    velocity = 0.0;
}

SpaceShip::~SpaceShip() {
}

void SpaceShip::init() {
    r_val = 0.0;
    g_val = 0.0;
    b_val = 0.0;
    velocity = 0.0;
    transform.rotation = 0.0;
    transform.position.x = 0.0;
    transform.position.y = 0.0;
    transform.scale.x = 2;
    transform.scale.y = 2;
}

void SpaceShip::update(float dt) {
    // reduce velocity by an amount of drag
    // move the ship

    transform.position.x += movement_direction.x * velocity * dt;
    transform.position.y += movement_direction.y * velocity * dt;

    if (velocity - drag < 0.0) {
        velocity = 0;
    }
    else {
        velocity -= drag;
    }
}

void SpaceShip::render() {

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(transform.position.x, transform.position.y, 0.0);
    glRotatef(transform.rotation, 0.0, 0.0, 1.0);
    glScalef(transform.scale.x, transform.scale.y, 0.0);

    glBegin(GL_POLYGON);
    glColor3f(235.0 / 255.0, 202.0 / 255.0, 59.0 / 255.0);
    glVertex3f(0.0, 0.5, 0.0);
    glVertex3f(-0.35, -0.35, 0.0);
    glVertex3f(0.0, -0.1, 0.0);
    glVertex3f(0.35, -0.35, 0.0);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0 / 255.0, 0.0 / 255.0, 0.0 / 255.0);
    glVertex3f(0.0, 0.5, 0.0);
    glVertex3f(-0.35, -0.35, 0.0);
    glVertex3f(0.0, -0.1, 0.0);
    glVertex3f(0.35, -0.35, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0 / 255.0, 0.0 / 255.0, 0.0 / 255.0);
    glVertex3f(0.0, 0.35, 0.0);
    glVertex3f(0.0, 0.9, 0.0);
    glEnd();

    glPopMatrix();
}


void SpaceShip::turn(bool clockwise) {
    if (clockwise) {
        transform.rotation += 5.0;
    }
    else {
        transform.rotation -= 5.0;
    }

    transform.rotation = fmod(transform.rotation, 360.0);
}

void SpaceShip::forward() {
    velocity = 3.0;

    float converted_rotation = transform.rotation - 90.0;
    if (converted_rotation < 0.0) {
        converted_rotation = 360.0 - converted_rotation;
    }

    float a_rad = converted_rotation / (180.0) * PI;
    movement_direction.x = sin(a_rad);
    movement_direction.y = cos(a_rad);

    printf("R %f \n x %f \n y%f\n", converted_rotation, movement_direction.x, movement_direction.y);
}
