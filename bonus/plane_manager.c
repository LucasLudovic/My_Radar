/*
** EPITECH PROJECT, 2023
** Plane manager
** File description:
** Handle the planes
*/

#include <stdio.h>
#include <math.h>
#include "my_macros.h"
#include "my_structs.h"
#include "plane_manager.h"
#include "simulation_manager.h"
#include "collision.h"
#include "grid.h"

static
void move_x(manager_t *manager, aircraft_t *aircraft, float delta_x,
    float dist)
{
    float speed_x = (delta_x / dist) * aircraft->speed;

    if (manager->fps > 1.f)
        speed_x = speed_x / manager->fps;
    else
        speed_x = speed_x * TIME_FRAME_MS / SECOND_IN_MS;
    aircraft->x_current += speed_x;
    if (aircraft->x_departure < aircraft->x_arrival) {
        if (aircraft->x_current < aircraft->x_arrival)
            return;
        aircraft->arrived = TRUE;
        return;
    }
    if (aircraft->x_departure > aircraft->x_arrival) {
        if (aircraft->x_current > aircraft->x_arrival)
            return;
        aircraft->arrived = TRUE;
        return;
    }
}

static
int check_arrived(aircraft_t *aircraft)
{
    if (aircraft->y_departure < aircraft->y_arrival &&
        aircraft->arrived == TRUE) {
        if (aircraft->y_current < aircraft->y_arrival) {
            aircraft->arrived = FALSE;
            return FAILURE;
        }
        aircraft->arrived = TRUE;
        return SUCCESS;
    }
    if (aircraft->y_departure > aircraft->y_arrival &&
    aircraft->arrived == TRUE) {
        if (aircraft->y_current > aircraft->y_arrival) {
            aircraft->arrived = FALSE;
            return FAILURE;
        }
        aircraft->arrived = TRUE;
        return SUCCESS;
    }
    return FAILURE;
}

static
void move_y(manager_t *manager, aircraft_t *aircraft, float delta_y,
    float dist)
{
    float speed_y = (delta_y / dist) * aircraft->speed;

    if (manager->fps > 1.f)
        speed_y = speed_y / manager->fps;
    else
        speed_y = speed_y * TIME_FRAME_MS / SECOND_IN_MS;
    aircraft->y_current += speed_y;
    if (check_arrived(aircraft) == SUCCESS)
        return;
    aircraft->arrived = FALSE;
}

static
int move_plane(manager_t *manager, aircraft_t *aircraft)
{
    float delta_x = aircraft->x_arrival - aircraft->x_departure;
    float delta_y = aircraft->y_arrival - aircraft->y_departure;
    float dist = sqrtf(delta_x * delta_x + delta_y * delta_y);
    float angle_radian = 0.f;
    float angle_degree = 0.f;

    if (aircraft == NULL)
        return FAILURE;
    move_x(manager, aircraft, delta_x, dist);
    move_y(manager, aircraft, delta_y, dist);
    angle_radian = (float)atan2((int)delta_y, (int)delta_x);
    angle_degree = angle_radian * 180.f / 3.14f;
    aircraft->rotation = angle_degree;
    return SUCCESS;
}

void display_single_plane(manager_t *manager, aircraft_t *aircraft, int i)
{
    if (manager->display_sprite == TRUE && aircraft[i].arrived != TRUE) {
        sfRenderWindow_drawSprite(manager->window,
            manager->plane_sprite, NULL);
    }
}

static
void display_plane_area(manager_t *manager, aircraft_t *aircraft,
    sfVector2f plane_position, int i)
{
    if (manager->display_area == TRUE && aircraft[i].arrived != TRUE) {
        sfRectangleShape_setPosition(manager->hitbox, plane_position);
        sfRectangleShape_setRotation(manager->hitbox, aircraft[i].rotation);
        sfRenderWindow_drawRectangleShape(manager->window, manager->hitbox,
            NULL);
    }
}

int display_plane(manager_t *manager, aircraft_t *aircraft)
{
    sfVector2f plane_position = { .x = 0, .y = 0 };
    int alive = 0;

    if (destroy_grid(manager) == NULL || initialize_grid(manager) == NULL)
        return alive;
    for (int i = 0; i < manager->nb_planes; i += 1) {
        if (aircraft[i].destroyed == TRUE || aircraft[i].arrived == TRUE)
            continue;
        alive += 1;
        if (aircraft[i].delay > sfTime_asSeconds(manager->timer))
            continue;
        move_plane(manager, &aircraft[i]);
        plane_position.x = aircraft[i].x_current;
        plane_position.y = aircraft[i].y_current;
        sfSprite_setPosition(manager->plane_sprite, plane_position);
        sfSprite_setRotation(manager->plane_sprite, aircraft[i].rotation);
        display_plane_area(manager, aircraft, plane_position, i);
        display_single_plane(manager, aircraft, i);
        add_plane_to_grid(manager, &aircraft[i]);
    }
    return alive;
}
