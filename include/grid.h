/*
** EPITECH PROJECT, 2023
** Collision
** File description:
** Header for the collision
*/

#ifndef GRID_H_
    #define GRID_H_
    #include "my_structs.h"

grid_t **initialize_grid(manager_t *manager);
void add_plane_to_grid(manager_t *manager, aircraft_t *aircraft);
void destroy_grid(manager_t *manager);

#endif
