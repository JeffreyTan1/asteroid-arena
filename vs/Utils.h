#pragma once
# include "Entity2D.h"
# include "SpaceShip.h"
# include "Walls.h"
# include "Asteroid.h"
# include "ParticleSystem.h"
# include "Drone.h"

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
# include <vector>
using std::vector;

bool detect_wall_collision(Entity2D* go, Entity2D* walls, float offset);
bool detect_objects_collision(Entity2D* o1, Entity2D* o2);
void render_game_ui(int score, float time, int wave_num, int win_height, int win_width);
void render_menu_ui(bool first_game, int win_height, int win_width);
void draw_circle_cartesian(float r, int n);
bool detect_asteroid_out_of_bounds(circle_t asteroid_circle, Entity2D* asteroid);
bool detect_line_ast_collision(line2d_t line, Asteroid* ast);
void set_ast_new_dir(line2d_t line, Asteroid* ast);
bool detect_ast_within_walls(Walls* walls, Asteroid* ast);
vec2f_t vec_normalize(vec2f_t v);
void spawn_asteroid(circle_t ast_circle, SpaceShip* space_ship, vector<Asteroid*>& asteroids, int num_ast);
void spawn_asteroid_splits(Asteroid* ast, vector<Asteroid*>& a_vec);
bool vector_contains_ast(vector<Asteroid*>& a_vec, Asteroid* element);
void set_ast_min_dist_apart(Asteroid* a1, Asteroid* a2);
void spawn_drone(SpaceShip* space_ship, vector<Drone*>& drones, vector<float>& times);

template <typename T>
void delete_clear_vector(T& v)
{
    for (int index = 0; index < v.size(); ++index)
    {
        delete v[index];
    }
    v.clear();
}


template <typename T>
void render_all_vector(T& v)
{
    for (int index = 0; index < v.size(); ++index)
    {
        v[index]->render();
    }
}

template <typename T>
void update_all_vector(T& v, float dt)
{
    for (int index = 0; index < v.size(); ++index)
    {
        v[index]->update(dt);
    }
}


template <typename T>
void spawn_projectile(T p, Entity2D* origin, vector<T>& vec, float offset)
{
    float converted_rotation = origin->transform.rotation + 90.0;

    if (converted_rotation > 360.0) {
        converted_rotation = converted_rotation - 360.0;
    }

    float a_rad = converted_rotation / (180.0) * PI;

    float x_pos = origin->transform.position.x + cos(a_rad) * offset;
    float y_pos = origin->transform.position.y + sin(a_rad) * offset;


    p->init(x_pos, y_pos, origin->transform.rotation);
    vec.push_back(p);
}

template <typename T>
void projectile_world_interactions(T& p_vec, Walls* walls,vector<Asteroid*>& a_vec, vector<ParticleSystem*>& ps_vec,
    int damage, int& score) {
    for (int i = 0; i < p_vec.size(); i++)
    {
        // Destroy missile if hits wall
        if (detect_wall_collision(p_vec[i], walls, 0.0)) {
            delete p_vec[i];
            p_vec.erase(p_vec.begin() + i);
            continue;
        }

        // Destroy missile and asteroid if hits asteroid
        for (int j = 0; j < a_vec.size(); j++)
        {
            if (detect_objects_collision(a_vec[j], p_vec[i])) {
                a_vec[j]->health -= damage;
                if (a_vec[j]->health <= 0) {
                    ParticleSystem* new_particle_system = new ParticleSystem();
                    new_particle_system->init(a_vec[j]->transform.position.x, a_vec[j]->transform.position.y,
                        a_vec[j]->transform.rotation, a_vec[j]->transform.scale.x, a_vec[j]->transform.scale.y);
                    ps_vec.push_back(new_particle_system);
                    if (!a_vec[j]->is_split) {
                        spawn_asteroid_splits(a_vec[j], a_vec);
                    }
                    delete a_vec[j];
                    a_vec.erase(a_vec.begin() + j);
                    score += 1;
                }
                delete p_vec[i];
                p_vec.erase(p_vec.begin() + i);
                break;
            }
        }
    }

}


