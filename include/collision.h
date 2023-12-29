/*
** EPITECH PROJECT, 2023
** Collision
** File description:
** Header for the collision
*/

#ifndef COLLISION_H_
    #define COLLISION_H_
    #include "my_structs.h"

int divide_grid(int x, int y, int size);
grid_t **initialize_grid(manager_t *manager);
void add_plane_to_grid(manager_t *manager, aircraft_t *aircraft);
void destroy_grid(manager_t *manager);

#endif
