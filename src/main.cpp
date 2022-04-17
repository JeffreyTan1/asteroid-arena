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
# include "Asteroid.h"
# include "Walls.h"
# include "Bullet.h"
# include "Missile.h"
# include "ParticleSystem.h"
# include "Drone.h"
# include "Utils.h"
# include "Types.h"
#include <cmath>
#include <vector>

using std::vector;

#define KEY_ESC 27
#define MOUSE_LEFT 0
#define DRONE_COST 10
#define MAX_ASTEROIDS 20
#define GUN_RATE 10.0
#define MISSILE_RATE 1.0
#define MENU_ASTEROID_RATE 0.5
#define SEC_PER_ASTEROID 5.0
#define GAME_TITLE "Asteroid Arena - Jeffrey Tan (S3851781)"

window_t g_mainwin;
bool key_states[256] = { 0 };
float world_size = 25.0;
float last_time = 0.0;
float last_bullet_time = 0.0;
float last_menu_asteroid_time = 0.0;
int wave_num = 0;
float last_wave_time = 0.0;
bool mouse_pressed = false;
bool w_pressed = false;
float start_time = 0.0;
int score = 0;
bool first_game = true;
bool game_over = true;

SpaceShip* space_ship = new SpaceShip();
Walls* walls = new Walls();
vector<Asteroid*> asteroids;
vector<Bullet*> bullets;
vector<Missile*> missiles;
vector<ParticleSystem*> particle_systems;
circle_t asteroid_circle = { 0.0, 0.0, 26.0 };
vector<Drone*> drones;
vector<float> drone_times;

void on_display()
{
    glClearColor(132.0 / 255.0, 94.0 / 255.0, 194.0 / 255.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    draw_circle_cartesian(asteroid_circle.radius, 64);

    walls->render();
    render_all_vector<vector<Asteroid*>>(asteroids);
    render_all_vector<vector<Bullet*>>(bullets);
    render_all_vector<vector<Missile*>>(missiles);
    render_all_vector<vector<ParticleSystem*>>(particle_systems);
    render_all_vector<vector<Drone*>>(drones);
    space_ship->render();

    if (game_over) {
        render_menu_ui(first_game, g_mainwin.height, g_mainwin.width);
    }
    else {
        render_game_ui(score, glutGet(GLUT_ELAPSED_TIME) / 1000.0 - start_time, wave_num,
            g_mainwin.height, g_mainwin.width);
    }


    int err;
    while ((err = glGetError()) != GL_NO_ERROR)
        printf("error: %s\n", gluErrorString(err));

    glutSwapBuffers();
}

void reset_game() {
    space_ship->init();
    walls->init();

    delete_clear_vector<vector<Asteroid*>>(asteroids);
    delete_clear_vector<vector<Bullet*>>(bullets);
    delete_clear_vector<vector<Missile*>>(missiles);
    delete_clear_vector<vector<ParticleSystem*>>(particle_systems);
    delete_clear_vector<vector<Drone*>>(drones);

    start_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    score = 0;
    wave_num = 0;
}

void start_game() {
    game_over = false;
    space_ship->is_dead = false;
}

void end_game() {
    first_game = false;
    game_over = true;
    space_ship->is_dead = true;
}

void run_key_events() {
    space_ship->turn(key_states['a'], key_states['d']);
    space_ship->boost(key_states['w']);
}

void on_idle()
{
    float cur_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    float dt = cur_time - last_time;
    last_time = cur_time;

    // Update 
    space_ship->update(dt);
    update_all_vector<vector<Asteroid*>>(asteroids, dt);
    update_all_vector<vector<Bullet*>>(bullets, dt);
    update_all_vector<vector<Missile*>>(missiles, dt);
    update_all_vector<vector<ParticleSystem*>>(particle_systems, dt);
    update_all_vector<vector<Drone*>>(drones, dt);

    projectile_world_interactions<vector<Bullet*>>(bullets, walls, asteroids, particle_systems, 1, score);
    projectile_world_interactions<vector<Missile*>>(missiles, walls, asteroids, particle_systems, 2, score);

    if (!game_over) {
        run_key_events();

        // Detect spaceship position to the arena walls
        if (detect_wall_collision(space_ship, walls, 1.5)) {
            walls->warn();
        }
        else {
            walls->safe();
        }
        if (detect_wall_collision(space_ship, walls, 0.0)) {
            end_game();
        }

        // Detect asteroids colliding with spaceship or leaving the spawn circle
        for (int i = 0; i < asteroids.size(); i++)
        {
            if (detect_objects_collision(asteroids[i], space_ship)) {
                end_game();
                continue;
            }
            if (detect_asteroid_out_of_bounds(asteroid_circle, asteroids[i])) {
                delete asteroids[i];
                asteroids.erase(asteroids.begin() + i);
            }
        }

        // Make missiles track the closest asteroid
        for (int i = 0; i < missiles.size(); i++)
        {
            Asteroid* closest_ast = nullptr;
            float closest_dist_sq = FLT_MAX;
            for (int j = 0; j < asteroids.size(); j++)
            {
                float dist_sq =
                    pow((asteroids[j]->transform.position.x - missiles[i]->transform.position.x), 2)
                    +
                    pow((asteroids[j]->transform.position.y - missiles[i]->transform.position.y), 2);

                bool closer = dist_sq < closest_dist_sq;

                closest_ast = closest_ast == nullptr ? asteroids[j] : closer ? asteroids[j] : closest_ast;
                closest_dist_sq = closer ? dist_sq : closest_dist_sq;
            }

            if (closest_ast != nullptr) {
                float x_diff = missiles[i]->transform.position.x - closest_ast->transform.position.x;
                float y_diff = missiles[i]->transform.position.y - closest_ast->transform.position.y;
                float angle_to_ast = atan2(y_diff, x_diff) * 180 / PI + 90.0;
                missiles[i]->transform.rotation = angle_to_ast;
            }
        }

        // Make asteroids bounce inside walls
        line2d_t wall_sides[4] = { walls->l_wall, walls->r_wall, walls->t_wall, walls->b_wall };
        for (int i = 0; i < asteroids.size(); i++)
        {
            for (int j = 0; j < sizeof(wall_sides); j++) {
                if (detect_ast_within_walls(walls, asteroids[i])) {
                    asteroids[i]->inside_walls = true;
                }

                if (detect_line_ast_collision(wall_sides[j], asteroids[i])) {
                    if (asteroids[i]->inside_walls) {
                        set_ast_new_dir(wall_sides[j], asteroids[i]);
                    }

                }
            }
        }

        // fire bullets (player)
        float dt_bullet = cur_time - last_bullet_time;
        int gun_type = space_ship->gun_type;
        float rate = gun_type == 0 ? GUN_RATE : MISSILE_RATE;

        if (dt_bullet > 1 / rate) {
            last_bullet_time = cur_time;
            if (mouse_pressed) {
                if (gun_type == 0) {
                    spawn_projectile<Bullet*>(new Bullet(), space_ship, bullets, 1.3);
                }
                else {
                    spawn_projectile<Missile*>(new Missile(), space_ship, missiles, 1.3);
                }
            }
        }
        
        // fire bullets (drones)
        for (int i = 0; i < drones.size(); i++) {
            float dt_drone_bullet = cur_time - drone_times[i];
            if (dt_drone_bullet > 1 / GUN_RATE) {
                drone_times[i] = cur_time;
                spawn_projectile<Bullet*>(new Bullet(), drones[i], bullets, 0.4);
            }
        }

        // rotate drones
        for (int i = 0; i < drones.size(); i++) {
            for (int j = 0; j < asteroids.size(); j++) {
                Asteroid* closest_ast = nullptr;
                float closest_dist_sq = FLT_MAX;
                for (int j = 0; j < asteroids.size(); j++)
                {
                    float dist_sq =
                        pow((asteroids[j]->transform.position.x - drones[i]->transform.position.x), 2)
                        +
                        pow((asteroids[j]->transform.position.y - drones[i]->transform.position.y), 2);

                    bool closer = dist_sq < closest_dist_sq;

                    closest_ast = closest_ast == nullptr ? asteroids[j] : closer ? asteroids[j] : closest_ast;
                    closest_dist_sq = closer ? dist_sq : closest_dist_sq;
                }

                if (closest_ast != nullptr) {
                    float x_diff = drones[i]->transform.position.x - closest_ast->transform.position.x;
                    float y_diff = drones[i]->transform.position.y - closest_ast->transform.position.y;
                    float angle_to_ast = atan2(y_diff, x_diff) * 180 / PI + 90.0;
                    drones[i]->transform.rotation = angle_to_ast;
                }
            }
        }

        
        // manage waves
        float dt_wave = cur_time - last_wave_time;
        if (dt_wave > wave_num * SEC_PER_ASTEROID || asteroids.size() == 0) {
            last_wave_time = cur_time;
            wave_num += 1;
            int asteroids_to_spawn = wave_num > MAX_ASTEROIDS ? MAX_ASTEROIDS : wave_num;
            spawn_asteroid(asteroid_circle, space_ship, asteroids, asteroids_to_spawn);
        }

        // Destroy drones in collided with asteroid
        for (int i = 0; i < asteroids.size(); i++)
        {
            for (int j = 0; j < drones.size(); j++) {
                if (detect_objects_collision(asteroids[i], drones[j])) {
                    delete drones[j];
                    drones.erase(drones.begin() + j);
                    drone_times.erase(drone_times.begin() + j);
                }
            }
        }

    }
    else {
        // Launch asteroids randomly during game_over state
        float dt_asteroid = cur_time - last_menu_asteroid_time;
        if (dt_asteroid > 1 / MENU_ASTEROID_RATE) {
            last_menu_asteroid_time = cur_time;
            spawn_asteroid(asteroid_circle, space_ship, asteroids, 1);
        }
    }


    // Make asteroids bounce against each other
    vector<Asteroid*> already_calculated_ast;
    for (int i = 0; i < asteroids.size(); i++)
    {
        for (int j = 0; j < asteroids.size(); j++) {
            if (i != j)
            {
                if (detect_objects_collision(asteroids[i], asteroids[j])) {
                    if (!vector_contains_ast(already_calculated_ast, asteroids[i]) && !vector_contains_ast(already_calculated_ast, asteroids[j]))
                    {
                        if (!detect_asteroid_out_of_bounds(asteroid_circle, asteroids[i]) && !detect_asteroid_out_of_bounds(asteroid_circle, asteroids[j])) {
                            already_calculated_ast.push_back(asteroids[i]);
                            already_calculated_ast.push_back(asteroids[j]);
                            line2d_t ast1 = {
                                {asteroids[i]->transform.position.x, asteroids[i]->transform.position.y},
                                {asteroids[i]->movement_direction.x, asteroids[i]->movement_direction.y}
                            };
                            line2d_t ast2 = {
                                {asteroids[j]->transform.position.x, asteroids[j]->transform.position.y},
                                {asteroids[j]->movement_direction.x, asteroids[j]->movement_direction.y}
                            };

                            set_ast_new_dir(ast1, asteroids[j]);
                            set_ast_new_dir(ast2, asteroids[i]);

                            set_ast_min_dist_apart(asteroids[j], asteroids[i]);
                        }
                        
                    }


                }
            }

        }
    }

    // remove expired particle systems
    for (int i = 0; i < particle_systems.size(); i++)
    {
        if (particle_systems[i]->expired) {
            delete particle_systems[i];
            particle_systems.erase(particle_systems.begin() + i);
        }
    }

    // remove expired drones
    for (int i = 0; i < drones.size(); i++)
    {
        if (drones[i]->expired) {
            delete drones[i];
            drones.erase(drones.begin() + i);
            drone_times.erase(drone_times.begin() + i);
        }
    }

    glutPostRedisplay();
}

void on_key_down(unsigned char key, int x, int y)
{
    if (key == KEY_ESC) {
        exit(EXIT_SUCCESS);
        return;
    }
    if (game_over) {
        reset_game();
        start_game();
    }
    else if (key == 'z') {
        space_ship->toggle_gun();
    }
    else if (key == 'x') {
        if (drones.size() < 2 && score >= DRONE_COST) {
            spawn_drone(space_ship, drones, drone_times);
            score -= DRONE_COST;
        }
    }
    else {
        key_states[key] = true;
    }
}

void on_key_up(unsigned char key, int x, int y)
{
    key_states[key] = false;
}

void on_mouse_press(int button, int state, int x, int y) {
    if (button == 0) {
        mouse_pressed = (state == 0);
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

    reset_game();
}

void init_app(int* argcp, char** argv, window_t* mainwinp)
{
    // GLUT & OpenGL setup
    glutInit(argcp, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // Display related setup
    glutCreateWindow(GAME_TITLE);
    if (mainwinp->is_fullscreen == true)
    {
        glutFullScreen();
    }
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    // Input setup
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(on_key_down);
    glutKeyboardUpFunc(on_key_up);
    glutMouseFunc(on_mouse_press);

    // Idle function & initialise game states
    glutIdleFunc(on_idle);
    last_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;

}

void run_app()
{
    glutMainLoop();
}

void load_config(int* argcp, char** argv, window_t* mainwin_p)
{
    mainwin_p->is_fullscreen = true;
}

int main(int argc, char** argv)
{
    load_config(&argc, argv, &g_mainwin);
    init_app(&argc, argv, &g_mainwin);
    run_app();
    return(EXIT_SUCCESS);
}
