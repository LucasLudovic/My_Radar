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
    sfEvent event;
} manager_t;

typedef struct aircraft_s {
    int x_departure;
    int y_departure;
    int x_arrival;
    int y_arrival;
    int speed;
    int delay;
}aircraft_t;

#endif
