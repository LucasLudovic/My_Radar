/*
** EPITECH PROJECT, 2023
** Struct
** File description:
** Struct for the project
*/

#ifndef MY_STRUCTS_H_
    #define MY_STRUCTS_H_
    #include <SFML/Graphics.h>

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
    sfEvent event;
    int display_area;
    int display_sprite;
    int nb_planes;
    int nb_towers;
} manager_t;

typedef struct aircraft_s {
    float x_departure;
    float y_departure;
    float x_current;
    float y_current;
    float x_arrival;
    float y_arrival;
    float speed;
    float delay;
    int arrived;
}aircraft_t;

typedef struct tower_s {
    float x_position;
    float y_position;
    float radius;
} tower_t;
#endif
