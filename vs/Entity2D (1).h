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

#define PI 3.14159265358979323846

typedef struct {
    float x;
    float y;
} vec2f_t;

typedef struct {
    vec2f_t position;
    float rotation;
    vec2f_t scale;
} transform2d_t;

class Entity2D
{
public:
    virtual void init() = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;
    transform2d_t transform = { { 0.0, 0.0 }, 0.0, { 0.0, 0.0 } };

protected:
    float r_val = 0.0;
    float g_val = 0.0;
    float b_val = 0.0;
    float velocity = 0.0;
    vec2f_t movement_direction;
};