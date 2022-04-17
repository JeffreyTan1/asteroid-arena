#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
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

# include "Entity2D.h"
# include "SpaceShip.h"
# include "Asteroid1.h"
# include "Asteroid2.h"
#include <cmath>

#define KEY_ESC 27
#define KEY_W 87
#define KEY_A 65
#define KEY_D 68
#define KEY_SPACE 32

#define GAME_TITLE "Asteroid Arena - Jeffrey Tan (S3851781)"

typedef struct
{
    int width, height, x_pos, y_pos;
    bool is_fullscreen;
} window_t;

window_t g_mainwin;
float world_size = 25.0f;

float g_last_time = 0.0;
int g_frame_count = 0;
float g_last_fps_time = 0.0;
int g_fps = 0;


SpaceShip* space_ship = new SpaceShip();
Entity2D* asteroid_1 = new Asteroid1();
Entity2D* asteroid_2 = new Asteroid2();

void game_object_init(Entity2D* go)
{
    go->init();
}

int detect_overlap(SpaceShip* c1, Entity2D* c2)
{
    const float dx = c2->transform.position.x - c1->transform.position.x;
    const float dy = c2->transform.position.y - c1->transform.position.y;

    const float radii =
        sqrt(c1->transform.scale.x + c1->transform.scale.y)
        + sqrt(c2->transform.scale.x + c2->transform.scale.y);

    if ((radii * radii) <= (dx * dx) + (dy * dy))
    {
        return 0;
    }

    return 1;
}

void render_ui(int fps) {
    glDisable(GL_DEPTH_TEST);
    char fps_text[100];
    snprintf(fps_text, 100, "FPS: %d", fps);
    int len = strlen(fps_text);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1280, 0, 1024);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(100, 900);
    for (int i = 0; i < len; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, fps_text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void render_frame(Entity2D* go)
{
    go->render();
}

void on_display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(89.0 / 255.0, 89.0 / 255.0, 89.0 / 255.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    render_frame(space_ship);
    render_frame(asteroid_1);
    render_frame(asteroid_2);
    render_ui(g_fps);

    int err;
    while ((err = glGetError()) != GL_NO_ERROR)
        printf("error: %s\n", gluErrorString(err));

    glutSwapBuffers();
}

void update_game_state(Entity2D* go, float dt)
{
    go->update(dt);
}

void on_idle()
{
    float cur_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    float dt = cur_time - g_last_time;
    update_game_state(space_ship, dt);
    update_game_state(asteroid_1, dt);
    update_game_state(asteroid_2, dt);
    g_last_time = cur_time;
    float dt_fps = cur_time - g_last_fps_time;
    g_frame_count += 1;
    if (g_frame_count % 20 == 0) {
        g_fps = (int)(20 / dt_fps);
        g_last_fps_time = cur_time;
    }

    glutPostRedisplay();
}

void on_key_press(unsigned char key, int x, int y)
{
    printf("Key press: %u", key);

    switch (key) {
    case KEY_ESC:
        exit(EXIT_SUCCESS);
        break;
    case KEY_A:
        space_ship->turn(true);
        break;
    case KEY_D:
        space_ship->turn(false);
        break;
    case KEY_W:
        space_ship->forward();
        break;
    default:
        break;
    }
}


void on_reshape(int w, int h)
{
    g_mainwin.width = w;
    g_mainwin.height = h;

    const float half_world_size = world_size / 2.0;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
    {
        float aspect = (float)h / (float)w;
        glOrtho(-half_world_size, half_world_size, -half_world_size * aspect, half_world_size * aspect, -half_world_size, half_world_size);
    }
    else
    {
        float aspect = (float)w / (float)h;
        glOrtho(-half_world_size * aspect, half_world_size * aspect, -half_world_size, half_world_size, -half_world_size, half_world_size);
    }

    game_object_init(space_ship);
    game_object_init(asteroid_1);
    game_object_init(asteroid_2);
}

void init_app(int* argcp, char** argv, window_t* mainwinp)
{
    // GLUT & OpenGL setup
    glutInit(argcp, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // Display related setup
    glutInitWindowPosition(mainwinp->x_pos, mainwinp->y_pos);
    glutInitWindowSize(mainwinp->width, mainwinp->height);
    glutCreateWindow(GAME_TITLE);
    if (mainwinp->is_fullscreen == true)
    {
        glutFullScreen();
    }
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    // Keyboard setup
    glutKeyboardFunc(on_key_press);

    // Idle function & initialise game states
    glutIdleFunc(on_idle);
    g_last_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;

}

void run_app()
{
    glutMainLoop();
}

void load_config(int* argcp, char** argv, window_t* mainwin_p)
{
    mainwin_p->width = 1024;
    mainwin_p->height = 768;
    mainwin_p->is_fullscreen = true;
}

int main(int argc, char** argv)
{
    load_config(&argc, argv, &g_mainwin);
    init_app(&argc, argv, &g_mainwin);
    run_app();
    return(EXIT_SUCCESS);
}
