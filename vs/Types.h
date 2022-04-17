#pragma once
typedef struct {
    float x;
    float y;
} vec2f_t;

typedef struct {
    vec2f_t position;
    float rotation;
    vec2f_t scale;
} transform2d_t;

typedef struct
{
    float pos_x;
    float pos_y;
    float radius;
} circle_t;

typedef struct
{
    int width, height, x_pos, y_pos;
    bool is_fullscreen;
} window_t;

typedef struct {
    vec2f_t position;
    vec2f_t direction;
} line2d_t;

