#include "Utils.h"


bool detect_wall_collision(Entity2D* go, Entity2D* walls, float offset)
{
    float left_wall_x = -walls->transform.scale.x;
    if (go->transform.position.x - go->circle.radius * go->transform.scale.x < left_wall_x + offset) {
        return true;
    }

    float right_wall_x = walls->transform.scale.x;
    if (go->transform.position.x + go->circle.radius * go->transform.scale.x > right_wall_x - offset) {
        return true;
    }

    float bottom_wall_x = -walls->transform.scale.y;
    if (go->transform.position.y - go->circle.radius * go->transform.scale.y < bottom_wall_x + offset) {
        return true;
    }

    float top_wall_x = walls->transform.scale.y;
    if (go->transform.position.y + go->circle.radius * go->transform.scale.y > top_wall_x - offset) {
        return true;
    }

    return false;
}

bool detect_objects_collision(Entity2D* o1, Entity2D* o2)
{
    float distance_sq = pow(o2->transform.position.x - o1->transform.position.x, 2)
        + pow(o2->transform.position.y - o1->transform.position.y, 2);

    return pow(o2->circle.radius * o2->transform.scale.x + o1->circle.radius * o1->transform.scale.x, 2) >= distance_sq;
}

bool detect_asteroid_out_of_bounds(circle_t asteroid_circle, Entity2D* asteroid)
{
    const float dx = asteroid->transform.position.x - 0.0;
    const float dy = asteroid->transform.position.y - 0.0;
    const float radii = asteroid_circle.radius + asteroid->circle.radius * asteroid->transform.scale.x;

    if ((radii * radii) <= (dx * dx) + (dy * dy))
    {
        return true;
    }

    return false;
}

float calculate_text_width(char* str, int str_len) {
    float width = 0.0;

    for (int i = 0; i < str_len; i++) {
        width += glutBitmapWidth(GLUT_BITMAP_9_BY_15, str[i]);
    }

    return width;
}

float get_text_height(void* font) {
    return  glutBitmapWidth(font, 'X') * (15.0 / 9.0);
}

void render_game_ui(int score, float time, int wave_num, int win_height, int win_width) {

    char score_text[100];
    snprintf(score_text, 100, "Score: %d", score);
    int score_len = strlen(score_text);
    float score_width = calculate_text_width(score_text, score_len);

    char time_text[100];
    snprintf(time_text, 100, "Time: %02d:%02d", int(time/60.0), int(time) % 60);
    int time_len = strlen(time_text);
    float time_width = calculate_text_width(time_text, time_len);

    char wave_text[100];
    snprintf(wave_text, 100, "Wave %d", wave_num);
    int wave_len = strlen(wave_text);
    float wave_width = calculate_text_width(wave_text, wave_len);

    float text_height = get_text_height(GLUT_BITMAP_9_BY_15);

    glDisable(GL_DEPTH_TEST);
    glColor3f(255.0 / 255.0, 255.0 / 255.0, 255.0 / 255.0);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, win_width, 0, win_height);
    glMatrixMode(GL_MODELVIEW);

    // render score
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(score_width * 1, win_height - text_height * 2);
    for (int i = 0; i < score_len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, score_text[i]);
    }
    glPopMatrix();

    // render time
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(win_width - time_width * 2, win_height - text_height * 2);
    for (int i = 0; i < time_len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, time_text[i]);
    }
    glPopMatrix();

    // render wave
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(win_width / 2.0 - 0.5 * wave_width, 0 + text_height * 2);
    for (int i = 0; i < wave_len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, wave_text[i]);
    }
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
}

void render_ui(int score, float time, int win_height, int win_width) {

    char score_text[100];
    snprintf(score_text, 100, "Score: %d", score);
    int score_len = strlen(score_text);
    float score_width = calculate_text_width(score_text, score_len);

    char time_text[100];
    snprintf(time_text, 100, "Time: %02d:%02d", int(time / 60.0), int(time) % 60);
    int time_len = strlen(time_text);
    float time_width = calculate_text_width(time_text, time_len);

    float text_height = get_text_height(GLUT_BITMAP_9_BY_15);

    glDisable(GL_DEPTH_TEST);
    glColor3f(255.0 / 255.0, 255.0 / 255.0, 255.0 / 255.0);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, win_width, 0, win_height);
    glMatrixMode(GL_MODELVIEW);

    // render score
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(score_width * 1, win_height - text_height * 2);
    for (int i = 0; i < score_len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, score_text[i]);
    }
    glPopMatrix();

    // render time
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(win_width - time_width * 2, win_height - text_height * 2);
    for (int i = 0; i < time_len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, time_text[i]);
    }
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
}

void render_menu_ui(bool first_game, int win_height, int win_width) {
    char menu_text[200];

    if (first_game) {
        snprintf(menu_text, 200, "Press any key to start...");
    }
    else {
        snprintf(menu_text, 200, "Game Over. Press any key to play again...");
    }

    int menu_text_len = strlen(menu_text);
    float menu_text_width = calculate_text_width(menu_text, menu_text_len);
    float text_height = get_text_height(GLUT_BITMAP_9_BY_15);

    glDisable(GL_DEPTH_TEST);
    glColor3f(255.0 / 255.0, 255.0 / 255.0, 255.0 / 255.0);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, win_width, 0, win_height);
    glMatrixMode(GL_MODELVIEW);

    // render menu
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(win_width / 2.0 - menu_text_width * 0.5, win_height / 2.0);
    for (int i = 0; i < menu_text_len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, menu_text[i]);
    }
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
}

void draw_circle_cartesian(float r, int n)
{
    float x, y;

    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);

    n /= 2;

    for (int i = 0; i < n; i++)
    {
        x = ((i / (float)n - 0.5) * 2.0) * r;
        y = sqrt(r * r - x * x);
        glVertex2f(x, y);
    }

    for (int i = n; i > 0; i--)
    {
        x = (i / (float)n - 0.5) * 2.0 * r;
        y = -sqrt(r * r - x * x);
        glVertex2f(x, y);
    }

    glEnd();
};

void render_all_vector(vector<Entity2D*>& v) {
    for (int i = 0; i < v.size(); i++)
    {
        v[i]->render();
    }
}

void delete_clear_vector(vector<Entity2D*>& v) {
    for (int i = 0; i < v.size(); i++)
    {
       delete v[i];
    }
    v.clear();
}

float dot(vec2f_t a, vec2f_t b) {
    return a.x * b.x + a.y * b.y;
}

vec2f_t vec_multiply(float magnitude, vec2f_t v) {
    v.x *= magnitude;
    v.y *= magnitude;
    return v;
}

vec2f_t vec_minus(vec2f_t a, vec2f_t b) {
    a.x -= b.x;
    a.y -= b.y;

    return a;
}

vec2f_t vec_normalize(vec2f_t v) {
    float magnitude = sqrt(v.x * v.x + v.y * v.y);
    return {v.x / magnitude , v.y / magnitude};
}

bool detect_line_ast_collision(line2d_t line, Asteroid* ast) {
    float dist = dot(ast->transform.position, line.direction) - dot(line.direction, line.position);
    return abs(dist) <= ast->circle.radius * ast->transform.scale.x;
}

void set_ast_new_dir(line2d_t line, Asteroid* ast) {
    vec2f_t old_dir = vec_normalize(ast->movement_direction);
    vec2f_t new_dir = vec_minus(old_dir, vec_multiply(2 * dot(old_dir, line.direction), line.direction));
    ast->movement_direction = new_dir;
}

bool detect_ast_within_walls(Walls* walls, Asteroid* ast) {
    bool result = true;
    float offset = 1.0;

    float left_wall_x = walls->l_wall.position.x;
    if (ast->transform.position.x - ast->circle.radius * ast->transform.scale.x < left_wall_x + offset) {
        result = false;
    }

    float right_wall_x = walls->r_wall.position.x;
    if (ast->transform.position.x + ast->circle.radius * ast->transform.scale.x > right_wall_x - offset) {
        result = false;
    }

    float bottom_wall_x = walls->t_wall.position.y;
    if (ast->transform.position.y - ast->circle.radius * ast->transform.scale.y < bottom_wall_x + offset) {
        result = false;
    }

    float top_wall_x = walls->b_wall.position.y;
    if (ast->transform.position.y + ast->circle.radius * ast->transform.scale.y > top_wall_x - offset) {
        result = false;
    }

    return result;

}

bool vector_contains_ast(vector<Asteroid*>& a_vec, Asteroid* element) {
    bool result = false;
    for (int i = 0; i < a_vec.size(); i++) {
        if (a_vec[i] == element) {
            result = true;
        }
    }
    return result;
}

void spawn_asteroid(circle_t asteroid_circle, SpaceShip* space_ship, vector<Asteroid*>& asteroids, int num_ast) {

    for (int i = 0; i < num_ast; i++)
    {
        Asteroid* new_asteroid = new Asteroid();

        // find a random place on circle
        int rand_degree = rand() % 360;
        float a_rad = rand_degree / (180.0) * PI;

        float x_pos = asteroid_circle.radius * cos(a_rad);
        float y_pos = asteroid_circle.radius * sin(a_rad);

        float x_diff = x_pos - space_ship->transform.position.x;
        float y_diff = y_pos - space_ship->transform.position.y;

        float angle_to_player = atan2(y_diff, x_diff) * 180 / PI + 90.0;

        new_asteroid->init(x_pos, y_pos, angle_to_player);
        asteroids.push_back(new_asteroid);
    }
}

void set_ast_min_dist_apart(Asteroid* a1, Asteroid* a2) {
    float x_diff = a1->transform.position.x - a2->transform.position.x;
    float y_diff = a1->transform.position.y - a2->transform.position.y;

    float dist_between = sqrt(
        pow(x_diff, 2)
        + pow(y_diff, 2)
    );

    float translation_needed = a1->circle.radius * a1->transform.scale.x + a2->circle.radius * a2->transform.scale.x
        - dist_between;

    translation_needed = translation_needed * 1.1; // for good measure

    if (translation_needed > 0.0) {
        float angle_to_a2 = atan2(y_diff, x_diff);
        a1->transform.position.x += cos(angle_to_a2) * translation_needed / 2.0;
        a1->transform.position.y += sin(angle_to_a2) * translation_needed / 2.0;

        a2->transform.position.x += cos(angle_to_a2 - PI / 2) * translation_needed / 2.0;
        a2->transform.position.y += sin(angle_to_a2 - PI / 2) * translation_needed / 2.0;

    }


}

void spawn_asteroid_splits(Asteroid* ast, vector<Asteroid*>& a_vec) {
    float ast_rad = atan2(ast->movement_direction.y, ast->movement_direction.x);
    float ast_deg = ast_rad * 180 / PI + 90;

    Asteroid* new_asteroid_1 = new Asteroid();
    Asteroid* new_asteroid_2 = new Asteroid();

    float new_scale_x = ast->transform.scale.x / 2.0;
    float new_scale_y = ast->transform.scale.y / 2.0;

    new_asteroid_1->init(
        ast->transform.position.x + ast->circle.radius * new_scale_x * 2 * cos(ast_rad + PI / 4.0),
        ast->transform.position.y + ast->circle.radius * new_scale_y * 2 * sin(ast_rad + PI / 4.0),
        ast_deg - 180 + 45,
        ast->velocity,
        ast->transform.scale.x / 2.0,
        ast->transform.scale.y / 2.0,
        true
    );

    new_asteroid_2->init(
        ast->transform.position.x + ast->circle.radius * new_scale_x * 2 * cos(ast_rad - PI / 4.0),
        ast->transform.position.y + ast->circle.radius * new_scale_y * 2 * sin(ast_rad - PI / 4.0),
        ast_deg - 180 - 45,
        ast->velocity,
        ast->transform.scale.x / 2.0,
        ast->transform.scale.y / 2.0,
        true
    );

    a_vec.push_back(new_asteroid_1);
    a_vec.push_back(new_asteroid_2);
}

void spawn_drone(SpaceShip* space_ship, vector<Drone*>& drones, vector<float>& times) {
    Drone* new_drone = new Drone();
    new_drone->init(space_ship->transform.position.x, space_ship->transform.position.y, space_ship->transform.rotation);
    drones.push_back(new_drone);
    times.push_back(0.0f);
}