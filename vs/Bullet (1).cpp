#include "Bullet.h"
#include <iostream>

using std::cout;
using std::endl;


Bullet::Bullet() {
    r_val, g_val, b_val = 0.0;
    velocity = 0.0;
}

Bullet::~Bullet() {
}

void Bullet::init() {
    r_val = 11.0;
    g_val = 252.0;
    b_val = 3.0;
    velocity = 1.0;
    transform.rotation = 30.0;
    transform.position.x = 0;
    transform.position.y = 0;
    transform.scale.x = 2;
    transform.scale.y = 2;
}

void Bullet::update(float dt) {
    
}

void Bullet::render() {

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(transform.position.x, transform.position.y, 0.0);
    glRotatef(transform.rotation, 0.0, 0.0, 1.0);
    glScalef(transform.scale.x, transform.scale.y, 0.0);

    glBegin(GL_LINE);
    glColor3f(r_val, g_val, b_val);
    glVertex3f(0.0, 0.2 , 0.0);
    glVertex3f(0.55 , 0.75 , 0.0);
    glEnd();

    glPopMatrix();
}