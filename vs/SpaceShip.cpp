#include "SpaceShip.h"

SpaceShip::SpaceShip() {
}

SpaceShip::~SpaceShip() {
}

void SpaceShip::init(float x_pos, float y_pos, float rot) {

}

void SpaceShip::init() {
    velocity = 0.0;
    transform.rotation = 0.0;
    transform.position.x = 0.0;
    transform.position.y = 0.0;
    transform.scale.x = 2.0;
    transform.scale.y = 2.0;
    circle.radius = 0.5;
    is_dead = true;
}

void SpaceShip::update(float dt) {
    // reduce velocity by an amount of drag move the ship
    if (is_boosting) {
        float new_velocity = velocity + VELOCITY_RATE_OF_CHANGE * dt;
        velocity = new_velocity > MAX_VELOCITY ? MAX_VELOCITY : new_velocity;
    }
    else {
        float new_velocity = velocity - VELOCITY_RATE_OF_CHANGE * dt;
        velocity = new_velocity < 0 ? 0 : new_velocity;
    }

    
    float new_rotation =transform.rotation + TURNING_RATE_OF_CHANGE * dt * turn_dir;

    if (new_rotation < 0.0) {
        new_rotation = 360.0 + new_rotation;
    }

    new_rotation = fmod(new_rotation, 360.0);

    transform.rotation = new_rotation;
    

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

void SpaceShip::render() {

    if (is_dead) {
        return;
    }

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(transform.position.x, transform.position.y, 0.0);
    glRotatef(transform.rotation, 0.0, 0.0, 1.0);
    glScalef(transform.scale.x, transform.scale.y, 0.0);

    if (gun_type == 0) {
        // Gun
        glBegin(GL_POLYGON);
        glColor3f(214.0 / 255.0, 93.0 / 255.0, 177.0 / 255.0);
        glVertex3f(0.0, 0.55, 0.0);
        glVertex3f(0.1, 0.45, 0.0);
        glVertex3f(0.0, 0.2, 0.0);
        glVertex3f(-0.1, 0.45, 0.0);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(255.0 / 255.0, 150.0 / 255.0, 113.0 / 255.0);
        glVertex3f(0.01, 0.55 - 0.005, 0.0);
        glVertex3f(0.0, 0.55, 0.0);
        glVertex3f(-0.01, 0.55 - 0.005, 0.0);
        glVertex3f(-0.01, 0.6, 0.0);
        glVertex3f(0.01, 0.6, 0.0);
        glEnd();
    }
    else {
        // Missle launcher

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
    }

    // Spaceship chassis
    glBegin(GL_POLYGON);
    glColor3f(255.0 / 255.0, 199.0 / 255.0, 95.0 / 255.0);
    glVertex3f(0.0, 0.5, 0.0);
    glVertex3f(-0.35, -0.35, 0.0);
    glVertex3f(0.0, -0.1, 0.0);
    glVertex3f(0.35, -0.35, 0.0);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(255.0 / 255.0, 150.0 / 255.0, 113.0 / 255.0);
    glVertex3f(0.0, 0.5, 0.0);
    glVertex3f(-0.35, -0.35, 0.0);
    glVertex3f(0.0, -0.1, 0.0);
    glVertex3f(0.35, -0.35, 0.0);
    glEnd();


    glPopMatrix();
}

void SpaceShip::turn(bool key_a, bool key_d) {
    if (key_a) {
        turn_dir = 1;
    }

    if (key_d) {
        turn_dir = -1;
    }
    
    if (key_a && key_d) {
        turn_dir = 0;
    }

    if (!key_a && !key_d) {
        turn_dir = 0;
    }
}

void SpaceShip::toggle_gun() {
    gun_type = gun_type == 0 ? 1 : 0;
}

void SpaceShip::boost(bool active) {
    is_boosting = active;
}
