#include "Missile.h"

Missile::Missile() {
}

Missile::~Missile() {
}

void Missile::init() {
    velocity = 4.0;
    transform.rotation = 0.0;
    transform.position.x = 0.0;
    transform.position.y = 0.0;
    transform.scale.x = 1.0;
    transform.scale.y = 1.0;
    circle.radius = 0.2;
}

void Missile::init(float x_pos, float y_pos, float rot) {
    velocity = 4.0;
    transform.rotation = rot;
    transform.position.x = x_pos;
    transform.position.y = y_pos;
    transform.scale.x = 1.0;
    transform.scale.y = 1.0;
    circle.radius = 0.2;
}

void Missile::update(float dt) {
    float converted_rotation = transform.rotation + 90.0;

    if (converted_rotation > 360.0) {
        converted_rotation = converted_rotation - 360.0;
    }

    float a_rad = converted_rotation / (180.0) * PI;

    movement_direction.x = cos(a_rad);
    movement_direction.y = sin(a_rad);

    transform.position.x += movement_direction.x * velocity * dt;
    transform.position.y += movement_direction.y * velocity * dt;
}

void Missile::render() {

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(transform.position.x, transform.position.y, 0.0);
    glRotatef(transform.rotation, 0.0, 0.0, 1.0);
    glScalef(transform.scale.x, transform.scale.y, 0.0);

    glBegin(GL_POLYGON);
    glColor3f(255.0 / 255.0, 150.0 / 255.0, 113.0 / 255.0);
    glVertex3f(-0.03, 0.3, 0.0);
    glVertex3f(-0.1, 0.15, 0.0);
    glVertex3f(-0.1, 0.35, 0.0);
    glVertex3f(-0.03, 0.4, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(255.0 / 255.0, 150.0 / 255.0, 113.0 / 255.0);
    glVertex3f(0.03, 0.3, 0.0);
    glVertex3f(0.1, 0.15, 0.0);
    glVertex3f(0.1, 0.35, 0.0);
    glVertex3f(0.03, 0.4, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(214.0 / 255.0, 93.0 / 255.0, 177.0 / 255.0);
    glVertex3f(0.03, 0.3, 0.0);
    glVertex3f(-0.03, 0.3, 0.0);
    glVertex3f(-0.03, 0.6, 0.0);
    glVertex3f(0.03, 0.6, 0.0);
    glEnd();

    glPopMatrix();
}