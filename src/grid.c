/*
** EPITECH PROJECT, 2023
** Grid
** File description:
** Handle the grid
*/

#include <stdlib.h>
#include <stdio.h>
#include "my_macros.h"
#include "my_structs.h"
#include "my.h"
#include "grid.h"

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
void destroy_grid_aircraft(manager_t *manager, int i)
{
    for (int j = 0; j < GRID_WIDTH; j += 1) {
        if (manager->grid[i][j].aircraft == NULL)
            continue;
        free(manager->grid[i][j].aircraft);
    }
}

grid_t **destroy_grid(manager_t *manager)
{
    if (manager == NULL || manager->grid == NULL)
        return manager->grid;
    for (int i = 0; i < GRID_HEIGHT; i += 1) {
        if (manager->grid[i] == NULL)
            continue;
        destroy_grid_aircraft(manager, i);
        free(manager->grid[i]);
    }
    free(manager->grid);
    return manager->grid;
}

static
int alloc_plane_grid(manager_t *manager, int i)
{
    for (int j = 0; j < GRID_WIDTH; j += 1) {
        manager->grid[i][j].aircraft = malloc(sizeof(aircraft_t *));
        manager->grid[i][j].nb_planes = 0;
        if (manager->grid[i][j].aircraft == NULL)
            return FAILURE;
    }
    return SUCCESS;
}

grid_t **initialize_grid(manager_t *manager)
{
    manager->grid = malloc(sizeof(grid_t *) * GRID_HEIGHT);
    if (manager->grid == NULL)
        return NULL;
    for (int i = 0; i < GRID_HEIGHT; i += 1) {
        manager->grid[i] = malloc(sizeof(grid_t) * GRID_WIDTH);
        if (manager->grid[i] == NULL)
            return NULL;
        if (alloc_plane_grid(manager, i) == FAILURE)
            return NULL;
    }
    return manager->grid;
}

static
void check_position(int *x, int *y)
{
    if (*x >= GRID_WIDTH)
        *x = GRID_WIDTH - 1;
    if (*y >= GRID_HEIGHT)
        *y = GRID_HEIGHT - 1;
    if (*x < 0)
        *x = 0;
    if (*y < 0)
        *y = 0;
}

static
int realloc_plane(grid_t *cell, aircraft_t *aircraft)
{
    aircraft_t **tmp = NULL;

    cell->aircraft[cell->nb_planes] = aircraft;
    cell->nb_planes += 1;
    tmp = malloc(sizeof(aircraft_t *) * (cell->nb_planes + 1));
    if (tmp == NULL)
        return FAILURE;
    tmp = my_memcpy(tmp, cell->aircraft,
        sizeof(aircraft_t *) * (cell->nb_planes));
    if (cell->aircraft != NULL)
        free(cell->aircraft);
    cell->aircraft = tmp;
    return SUCCESS;
}

void add_plane_to_grid(manager_t *manager, aircraft_t *aircraft)
{
    int x = (int)aircraft->x_current / SPRITE_SIZE;
    int y = (int)aircraft->y_current / SPRITE_SIZE;
    grid_t *cell = NULL;

    check_position(&x, &y);
    if (manager == NULL || manager->grid == NULL || manager->grid[y] == NULL)
        return;
    cell = &manager->grid[y][x];
    if (cell == NULL || cell->aircraft == NULL)
        return;
    if (realloc_plane(cell, aircraft) == FAILURE)
        return;
}
