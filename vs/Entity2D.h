#pragma once

#if _WIN32
# include <windows.h>
#endif
#if __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif
#include <stdio.h>
# include "Types.h"
# include <cmath>
#define PI 3.14159265358979323846

class Entity2D
{
public:
    virtual void init() = 0;
    virtual void init(float x_pos, float y_pos, float rot) = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;
    transform2d_t transform = { { 0.0, 0.0 }, 0.0, { 0.0, 0.0 } };
    circle_t circle = {0.0, 0.0, 0.0};
    vec2f_t movement_direction = { 0.0, 0.0 };
    float velocity = 0.0;

protected:
    void draw_circle_cartesian(float rad, int n_vert)
    {
        float x, y;

        glLineWidth(2.0);
        glBegin(GL_LINE_LOOP);

        n_vert /= 2;

        for (int i = 0; i < n_vert; i++)
        {
            x = ((i / (float)n_vert - 0.5) * 2.0) * rad;
            y = sqrt(rad * rad - x * x);
            glVertex2f(x, y);
        }

        for (int i = n_vert; i > 0; i--)
        {
            x = (i / (float)n_vert - 0.5) * 2.0 * rad;
            y = -sqrt(rad * rad - x * x);
            glVertex2f(x, y);
        }

        glEnd();
    };
};