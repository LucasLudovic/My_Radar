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
#include "collision.h"

static
void move_x(aircraft_t *aircraft)
{
    float speed = aircraft->speed * TIME_FRAME_MS / SECOND_IN_MS;

    if (aircraft->x_departure < aircraft->x_arrival) {
        if (aircraft->x_current < aircraft->x_arrival) {
            aircraft->x_current += speed;
            return;
        }
        aircraft->arrived = TRUE;
        return;
    }
    if (aircraft->x_departure > aircraft->x_arrival) {
        if (aircraft->x_current > aircraft->x_arrival) {
            aircraft->x_current -= speed;
            return;
        }
        aircraft->arrived = TRUE;
        return;
    }
}

static
void move_y(aircraft_t *aircraft)
{
    float speed = aircraft->speed * TIME_FRAME_MS / SECOND_IN_MS;

    if (aircraft->y_departure < aircraft->y_arrival) {
        if (aircraft->y_current < aircraft->y_arrival) {
            aircraft->y_current += speed;
            return;
        }
        aircraft->arrived = TRUE;
        return;
    }
    if (aircraft->y_departure > aircraft->y_arrival) {
        if (aircraft->y_current > aircraft->y_arrival) {
            aircraft->y_current -= speed;
            return;
        }
        aircraft->arrived = TRUE;
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
        plane_position.x = aircraft[i].x_current;
        plane_position.y = aircraft[i].y_current;
        sfSprite_setPosition(manager->plane_sprite, plane_position);
        if (manager->display_area == TRUE && aircraft[i].arrived != TRUE) {
            sfRectangleShape_setPosition(manager->hitbox, plane_position);
            sfRenderWindow_drawRectangleShape(manager->window, manager->hitbox,
                NULL);
        }
        if (manager->display_sprite == TRUE && aircraft[i].arrived != TRUE) {
            sfRenderWindow_drawSprite(manager->window,
                manager->plane_sprite, NULL);
        }
        add_plane_to_grid(manager, &aircraft[i]);
    }
    destroy_grid(manager);
    initialize_grid(manager);
}
