/*
** EPITECH PROJECT, 2023
** Collision
** File description:
** Handle the collision
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "my_macros.h"
#include "my_structs.h"
#include "my.h"

static
void collide_single_plane(manager_t *manager, aircraft_t *plane_to_collide, aircraft_t *plane)
{
    if (plane_to_collide == NULL || plane == NULL)
        return;
    if (plane->destroyed == TRUE || plane_to_collide->destroyed == TRUE)
        return;
    int overlap_x = abs((int)(plane->x_current - plane_to_collide->x_current))< (int)(RECT);
    int overlap_y = abs((int)(plane->y_current - plane_to_collide->y_current))< (int)(RECT);

    if (overlap_x && overlap_y) {
        plane_to_collide->destroyed = TRUE;
        plane->destroyed = TRUE;
    }
    /*x_collide = (int)plane_to_collide->x_current;
    y_collide = (int)plane_to_collide->y_current;
    if (abs((int)plane->x_current - x_collide) <= SPRITE_SIZE &&
        abs((int)plane->y_current - y_collide) <= SPRITE_SIZE &&
        plane->destroyed != TRUE && plane_to_collide->destroyed != TRUE) {
        plane->destroyed = TRUE;
        plane_to_collide->destroyed = TRUE;
    }*/
}

static
void check_side(manager_t *manager, aircraft_t *plane, int i, int j)
{
    grid_t *cell_top = NULL;
    aircraft_t *plane_to_collide = NULL;
    int plane_to_collide_with = 0;

    if (manager == NULL || manager->grid == NULL || i >= GRID_HEIGHT ||
        j >= GRID_WIDTH || i < 0 || j < 0 || manager->grid[i] == NULL)
        return;
    cell_top = &manager->grid[i][j];
    if (cell_top == NULL)
        return;
    while (plane_to_collide_with < cell_top->nb_planes) {
        plane_to_collide = cell_top->aircraft[plane_to_collide_with];
        if (plane_to_collide == plane) {
            plane_to_collide_with += 1;
            continue;
        }
        collide_single_plane(manager, plane_to_collide, plane);
        plane_to_collide_with += 1;
    }
}

static
void collide_with_sides(manager_t *manager, aircraft_t *plane, int i, int j)
{
    if (manager == NULL || plane == NULL)
        return;
    if (i > 0)
        check_side(manager, plane, i - 1, j);
    if (i > 0 && j > 0)
        check_side(manager, plane, i - 1, j - 1);
    if (i > 0 && j < GRID_WIDTH - 1)
        check_side(manager, plane, i -1, j + 1);
    if (i < GRID_HEIGHT - 1)
        check_side(manager, plane, i + 1, j);
    if (i < GRID_HEIGHT - 1 && j > 0)
        check_side(manager, plane, i + 1, j - 1);
    if (i < GRID_HEIGHT- 1 && j < GRID_WIDTH - 1)
        check_side(manager, plane, i + 1, j + 1);
    if (j > 0)
        check_side(manager, plane, i, j - 1);
    if (j < GRID_WIDTH - 1)
        check_side(manager, plane, i, j + 1);
}

static
int check_tower(manager_t *manager, tower_t *tower, aircraft_t *aircraft)
{
    float dx = 0.f;
    float dy = 0.f;
    float dist = 0.f;

    for (int i = 0; i < manager->nb_towers; i += 1) {
        if (tower == NULL || aircraft == NULL)
            return FALSE;
        dx = tower[i].x_position - aircraft->x_current;
        dy = tower[i].y_position - aircraft->y_current;
        dist = sqrtf(dx * dx + dy * dy);
        if (dist <= tower[i].radius + SPRITE_SIZE) {
            return TRUE;
        }
    }
    return FALSE;
}

static
void check_single_case(manager_t *manager, tower_t *tower, int i, int j)
{
    int plane_check = 0;
    grid_t *cell = NULL;

    if (manager == NULL || manager->grid == NULL || i >= GRID_HEIGHT ||
        j >= GRID_WIDTH || i < 0 || j < 0 || manager->grid[i] == NULL)
        return;
    cell = &manager->grid[i][j];
    while (plane_check < cell->nb_planes) {
        if (cell->aircraft[plane_check]->arrived == TRUE ||
            cell->aircraft[plane_check]->destroyed == TRUE ||
            check_tower(manager, tower, cell->aircraft[plane_check]) == TRUE) {
            plane_check += 1;
            continue;
        }
        check_side(manager, cell->aircraft[plane_check], i, j);
        collide_with_sides(manager, cell->aircraft[plane_check], i, j);
        plane_check += 1;
    }
}

void check_collision(manager_t *manager, tower_t *tower)
{
    for (int i = 0; i < GRID_HEIGHT; i += 1) {
        for (int j = 0; j < GRID_WIDTH; j += 1) {
            check_single_case(manager, tower, i, j);
        }
    }
}
