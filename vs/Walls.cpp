#include "Walls.h"

Walls::Walls() {
    r = 255.0;
    g = 255.0;
    b = 255.0;
}

Walls::~Walls() {
}

void Walls::init(float x_pos, float y_pos, float rot) {
}

void Walls::init() {
    velocity = 0.0;
    transform.rotation = 0.0;
    transform.position.x = 0;
    transform.position.y = 0;
    transform.scale.x = 21.0;
    transform.scale.y = 11.0;
    l_wall = { {-1.0f * transform.scale.x, 0.0}, {1.0, 0.0} };
    r_wall = { {1.0f * transform.scale.x, 0.0}, {1.0, 0.0} };
    t_wall = { {0.0, -1.0f * transform.scale.y}, {0.0, 1.0} };
    b_wall = { {0.0, 1.0f * transform.scale.y}, {0.0, 1.0} };
}

void Walls::update(float dt) {
}

void Walls::render() {
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(transform.position.x, transform.position.y, 0.0);
    glRotatef(transform.rotation, 0.0, 0.0, 1.0);
    glScalef(transform.scale.x, transform.scale.y, 0.0);
    glBegin(GL_LINE_LOOP);
    glColor3f(r / 255.0, g / 255.0, b / 255.0);
    glVertex3f(-1.0, -1.0, 0.0);
    glVertex3f(1.0, -1.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(-1.0, 1.0, 0.0);
    glEnd();
    glPopMatrix();
}

void Walls::warn() {
    r = 255.0;
    g = 0.0;
    b = 0.0;
}

void Walls::safe() {
   r = 255.0;
   g = 255.0;
   b = 255.0;
}