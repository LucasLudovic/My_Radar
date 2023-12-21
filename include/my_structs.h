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
    sfEvent event;
    int display_area;
    int display_sprite;
    int nb_planes;
    int nb_towers;
} manager_t;

typedef struct aircraft_s {
    int x_departure;
    int y_departure;
    int x_current;
    int y_current;
    int x_arrival;
    int y_arrival;
    int speed;
    int delay;
    int arrived;
}aircraft_t;

typedef struct tower_s {
    int x_position;
    int y_position;
    int radius;
} tower_t;
#endif
