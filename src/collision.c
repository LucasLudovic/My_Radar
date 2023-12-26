/*
** EPITECH PROJECT, 2023
** Collision
** File description:
** Handle the collision
*/

#include <stdlib.h>
#include "my_macros.h"
#include "my_structs.h"
#include "my.h"

int divide_grid(int x, int y, int size)
{
    int index_x = x / size;
    int index_y = y / size;
    int sum = index_x + (index_y * WIDTH);

    return sum;
}

grid_t **initialize_grid(manager_t *manager)
{
    manager->grid = malloc(sizeof(grid_t *) * HEIGHT_WIDTH);
    for (int i = 0; i < HEIGHT_WIDTH; i += 1) {
        manager->grid[i] = malloc(sizeof(grid_t) * GRID_WIDTH);
    }
    return manager->grid;
}
