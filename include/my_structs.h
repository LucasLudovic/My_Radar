/*
** EPITECH PROJECT, 2023
** Struct
** File description:
** Struct for the project
*/

#ifndef MY_STRUCTS_H_
    #define MY_STRUCTS_H_
    #include <SFML/Graphics.h>

typedef struct aircraft_s {
    float x_departure;
    float y_departure;
    float x_current;
    float y_current;
    float x_arrival;
    float y_arrival;
    float speed;
    float delay;
    float rotation;
    int destroyed;
    int arrived_x;
    int arrived_y;
    int arrived;
}aircraft_t;

typedef struct tower_s {
    float x_position;
    float y_position;
    float radius;
} tower_t;

typedef struct grid_s {
    aircraft_t **aircraft;
    tower_t *tower;
    int nb_planes;
    int nb_towers;
} grid_t;

typedef struct manager_s {
    sfRenderWindow *window;
    sfTexture *plane_texture;
    sfTexture *tower_texture;
    sfTexture *background_texture;
    sfSprite *plane_sprite;
    sfSprite *tower_sprite;
    sfSprite *background_sprite;
    sfRectangleShape *hitbox;
    sfCircleShape *tower_radius;
    sfTime timer;
    sfEvent event;
    float fps;
    int display_area;
    int display_sprite;
    int nb_planes;
    int nb_towers;
    grid_t **grid;
} manager_t;

typedef struct sim_timer_s {
    int hours;
    int minutes;
    int seconds;
    char *hours_str;
    char *minutes_str;
    char *seconds_str;
} sim_timer_t;

#endif
