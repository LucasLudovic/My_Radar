/*
** EPITECH PROJECT, 2023
** Collision
** File description:
** Handle the collision
*/

#include <stdlib.h>
#include <stdio.h>
#include "my_macros.h"
#include "my_structs.h"
#include "my.h"

void *my_memcpy(void *dest, void *src, size_t size)
{
    char *dest_cpy = (char *)dest;
    char *src_cpy = (char *)src;

    if (dest == NULL || src == NULL)
        return NULL;
    for (size_t i = 0; i < size; i += 1)
        dest_cpy[i] = src_cpy[i];
    return dest;
}

static
int destroy_grid_aircraft(manager_t *manager, int i) {
    for (int j = 0; j < GRID_WIDTH; j += 1) {
        if (manager->grid[i][j].aircraft == NULL)
            return FAILURE;
        free(manager->grid[i][j].aircraft);
    }
    return SUCCESS;
}

void destroy_grid(manager_t *manager)
{
    if (manager == NULL)
        return;
    for (int i = 0; i < HEIGHT_WIDTH; i += 1) {
        if (manager->grid[i] == NULL)
            return;
        if (destroy_grid_aircraft(manager, i) == FAILURE)
            return;
    }
}

grid_t **initialize_grid(manager_t *manager)
{
    manager->grid = malloc(sizeof(grid_t *) * HEIGHT_WIDTH);
    for (int i = 0; i < HEIGHT_WIDTH; i += 1) {
        manager->grid[i] = malloc(sizeof(grid_t) * GRID_WIDTH);
        for (int j = 0; j < GRID_WIDTH; j += 1) {
            manager->grid[i][j].aircraft = malloc(sizeof(aircraft_t *));
            manager->grid[i][j].nb_planes = 0;
        }
    }
    return manager->grid;
}

void add_plane_to_grid(manager_t *manager, aircraft_t *aircraft)
{
    int x = (int)aircraft->x_current / SPRITE_SIZE;
    int y = (int)aircraft->y_current / SPRITE_SIZE;
    grid_t *cell = &manager->grid[y][x];
    aircraft_t **tmp = NULL;

    if (cell == NULL)
        return;
    cell->aircraft[cell->nb_planes] = aircraft;
    cell->nb_planes += 1;
    tmp = malloc(sizeof(aircraft_t *) * (cell->nb_planes + 1));
    if (tmp == NULL)
        return;
    tmp = my_memcpy(tmp, cell->aircraft,
        sizeof(aircraft_t *) * cell->nb_planes);
    free(cell->aircraft);
    cell->aircraft = tmp;
}
