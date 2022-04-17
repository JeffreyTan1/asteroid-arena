#include "Asteroid.h"

Asteroid::Asteroid() {
}

Asteroid::~Asteroid() {
}

void Asteroid::init(float x_pos, float y_pos, float rot) {
    int rand_vel = rand() % 500 + 250;
    velocity = rand_vel / 100.0;
    transform.rotation = rot;
    transform.position.x = x_pos;
    transform.position.y = y_pos;

    int rand_size = rand() % 150 + 50;
    transform.scale.x = rand_size / 100.0;
    transform.scale.y = rand_size / 100.0;

    circle.radius = 1.0;

    health = transform.scale.x > 1.0 ? 3 : 2;

    type = rand() % 2;

    float converted_rotation = transform.rotation + 90.0;
    if (converted_rotation > 360.0) {
        converted_rotation = converted_rotation - 360.0;
    }
    float a_rad = converted_rotation / (180.0) * PI;

    movement_direction.x = cos(a_rad);
    movement_direction.y = sin(a_rad);

    rot_rate = rand() % 2 + 0.5 / 10;
    rot_dir = rand() % 2 == 0 ? -1 : 1;
}

void Asteroid::init() {
}

void Asteroid::init(float x_pos, float y_pos, float rot, float vel, float scale_x, float scale_y, float is_split) {
    transform.position.x = x_pos;
    transform.position.y = y_pos;
    transform.rotation = rot;
    velocity = vel;
    transform.scale.x = scale_x;
    transform.scale.y = scale_y;
    circle.radius = 1.0;
    health = transform.scale.x > 1.0 ? 3 : 2;
    type = rand() % 2;

    float converted_rotation = transform.rotation + 90.0;
    if (converted_rotation > 360.0) {
        converted_rotation = converted_rotation - 360.0;
    }
    float a_rad = converted_rotation / (180.0) * PI;

    movement_direction.x = cos(a_rad);
    movement_direction.y = sin(a_rad);

    rot_rate = rand() % 2 + 0.5 / 10;
    rot_dir = rand() % 2 == 0 ? -1 : 1;

    this->is_split = is_split;
}

void Asteroid::update(float dt) {
    transform.rotation += rot_rate * rot_dir;

    transform.position.x += movement_direction.x * velocity * dt;
    transform.position.y += movement_direction.y * velocity * dt;
}

void Asteroid::render() {
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(transform.position.x, transform.position.y, 0.0);
    glRotatef(transform.rotation, 0.0, 0.0, 1.0);
    glScalef(transform.scale.x, transform.scale.y, 0.0);

    if (type == 0) {
        glBegin(GL_POLYGON);
        glColor3f(214.0 / 255.0, 93.0 / 255.0, 177.0 / 255.0);
        glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(0.5, 0.8, 0.0);
        glVertex3f(1.0, -0.2, 0.0);
        glVertex3f(0.35, -1.0, 0.0);
        glVertex3f(-0.6, -0.9, 0.0);
        glVertex3f(-0.1, -0.5, 0.0);
        glVertex3f(-0.8, -0.55, 0.0);
        glVertex3f(-0.7, 0.2, 0.0);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glColor3f(255.0 / 255.0, 199.0 / 255.0, 95.0 / 255.0);
        glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(0.5 , 0.8 , 0.0);
        glVertex3f(1.0, -0.2 , 0.0);
        glVertex3f(0.35 , -1.0, 0.0);
        glVertex3f(-0.6 , -0.9 , 0.0);
        glVertex3f(-0.1 , -0.5 , 0.0);
        glVertex3f(-0.8 , -0.55 , 0.0);
        glVertex3f(-0.7 ,  0.2 , 0.0);
        glEnd();
    }
    else {

        glBegin(GL_POLYGON);
        glColor3f(214.0 / 255.0, 93.0 / 255.0, 177.0 / 255.0);
        glVertex3f(0.0, 0.2, 0.0);
        glVertex3f(0.55, 0.75, 0.0);
        glVertex3f(1.0, 0.1, 0.0);
        glVertex3f(0.8, -0.7, 0.0);
        glVertex3f(0.0, -1.0, 0.0);
        glVertex3f(-0.85, -0.85, 0.0);
        glVertex3f(-0.55, -0.2, 0.0);
        glVertex3f(-1.0, -0.05, 0.0);
        glVertex3f(-0.5, 1.0, 0.0);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glColor3f(255.0 / 255.0, 199.0 / 255.0, 95.0 / 255.0);
        glVertex3f(0.0, 0.2, 0.0);
        glVertex3f(0.55, 0.75, 0.0);
        glVertex3f(1.0, 0.1, 0.0);
        glVertex3f(0.8, -0.7, 0.0);
        glVertex3f(0.0, -1.0, 0.0);
        glVertex3f(-0.85, -0.85, 0.0);
        glVertex3f(-0.55, -0.2, 0.0);
        glVertex3f(-1.0, -0.05, 0.0);
        glVertex3f(-0.5, 1.0, 0.0);
        glEnd();
    }
    glPopMatrix();
}