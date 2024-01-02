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

static
void collide_single_plane(aircraft_t *plane_to_collide, aircraft_t *plane)
{
    int x_collide = 0;
    int y_collide = 0;

    x_collide = (int)plane_to_collide->x_current;
    y_collide = (int)plane_to_collide->y_current;
    if (abs((int)plane->x_current - x_collide) <= SPRITE_SIZE &&
        abs((int)plane->y_current - y_collide) <= SPRITE_SIZE &&
        plane->destroyed != TRUE && plane_to_collide->destroyed != TRUE) {
        plane->destroyed = TRUE;
        plane_to_collide->destroyed = TRUE;
    }
}

static
void check_side(manager_t *manager, aircraft_t *plane, int i, int j)
{
    grid_t *cell_top = NULL;
    aircraft_t *plane_to_collide = NULL;
    int plane_to_collide_with = 0;

    cell_top = &manager->grid[i][j];
    while (plane_to_collide_with < cell_top->nb_planes) {
        plane_to_collide = cell_top->aircraft[plane_to_collide_with];
        if (plane_to_collide == plane) {
            plane_to_collide_with += 1;
            continue;
        }
        collide_single_plane(plane_to_collide, plane);
        plane_to_collide_with += 1;
    }
}

static
void collide_with_sides(manager_t *manager, aircraft_t *plane, int i, int j)
{
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
int check_if_tower(manager_t *manager, tower_t *tower, aircraft_t *aircraft)
{
    for (int i = 0; i < manager->nb_towers; i += 1) {
        if (tower == NULL || aircraft == NULL)
            return FALSE;
        printf("Radius : %f\n", tower[i].radius);
        if (tower[i].x_position >= aircraft->x_current && tower[i].x_position - tower[i].radius <= aircraft->x_current) {
            if (tower[i].y_position >= aircraft->y_current && tower[i].y_position - tower[i].radius <= aircraft->y_current)
                return TRUE;
            if (tower[i].y_position <= aircraft->y_current && tower[i].y_position + tower[i].radius >= aircraft->y_current)
                return TRUE;
        }
        if (tower[i].x_position <= aircraft->x_current && tower[i].x_position + tower[i].radius >= aircraft->x_current) {
            if (tower[i].y_position >= aircraft->y_current && tower[i].y_position - tower[i].radius <= aircraft->y_current)
                return TRUE;
            if (tower[i].y_position <= aircraft->y_current && tower[i].y_position + tower[i].radius >= aircraft->y_current)
                return TRUE;
        }
    }
    return FALSE;
}

static
void check_single_case(manager_t *manager, tower_t *tower, int i, int j)
{
    int plane_checked = 0;
    grid_t *cell = NULL;

    cell = &manager->grid[i][j];
    while (plane_checked < cell->nb_planes) {
        if (check_if_tower(manager, tower, cell->aircraft[plane_checked]) == TRUE) {
            plane_checked += 1;
            continue;
        }
        check_side(manager, cell->aircraft[plane_checked], i, j);
        collide_with_sides(manager, cell->aircraft[plane_checked], i, j);
        plane_checked += 1;
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
