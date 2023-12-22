/*
** EPITECH PROJECT, 2023
** Plane manager
** File description:
** Handle the planes
*/

#include "my_macros.h"
#include "my_structs.h"
#include "plane_manager.h"
#include "simulation_manager.h"

static
void move_x(aircraft_t *aircraft)
{
    if (aircraft->x_departure < aircraft->x_arrival) {
        if (aircraft->x_current < aircraft->x_arrival) {
            aircraft->x_current += aircraft->speed;
            return;
        }
        aircraft->arrived = 1;
        return;
    }
    if (aircraft->x_departure > aircraft->x_arrival) {
        if (aircraft->x_current > aircraft->x_arrival) {
            aircraft->x_current -= aircraft->speed;
            return;
        }
        aircraft->arrived = 1;
        return;
    }
}

static
void move_y(aircraft_t *aircraft)
{
    if (aircraft->y_departure < aircraft->y_arrival) {
        if (aircraft->y_current < aircraft->y_arrival) {
            aircraft->y_current += aircraft->speed;
            return;
        }
        aircraft->arrived = 1;
        return;
    }
    if (aircraft->y_departure > aircraft->y_arrival) {
        if (aircraft->y_current > aircraft->y_arrival) {
            aircraft->y_current -= aircraft->speed;
            return;
        }
        aircraft->arrived = 1;
        return;
    }
}

int move_plane(aircraft_t *aircraft)
{
    if (aircraft == NULL)
        return FAILURE;
    move_x(aircraft);
    move_y(aircraft);
    return SUCCESS;
}

void display_plane(manager_t *manager, aircraft_t *aircraft)
{
    sfVector2f plane_position = { .x = 0, .y = 0 };

    for (int i = 0; i < manager->nb_planes; i += 1) {
        move_plane(&aircraft[i]);
        plane_position.x = (float)aircraft[i].x_current;
        plane_position.y = (float)aircraft[i].y_current;
        sfSprite_setPosition(manager->plane_sprite, plane_position);
        plane_position.x += HALF_SPRITE;
        plane_position.y += HALF_SPRITE;
        sfSprite_setOrigin(manager->plane_sprite, plane_position);
        if (manager->display_sprite == 1 && aircraft[i].arrived != 1) {
            sfRenderWindow_drawSprite(manager->window,
                manager->plane_sprite, NULL);
        }
    }
}
