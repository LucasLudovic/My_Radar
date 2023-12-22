/*
** EPITECH PROJECT, 2023
** Plane manager
** File description:
** Handle the planes
*/

#include "my_macros.h"
#include "my_structs.h"
#include "plane_manager.h"
#include "tower_manager.h"

static
void display_area(manager_t *manager, tower_t *tower, int i,
    sfVector2f tower_position)
{
    if (manager->display_area == TRUE) {
        sfCircleShape_setPosition(manager->tower_radius, tower_position);
        sfCircleShape_setRadius(manager->tower_radius, tower[i].radius);
        sfRenderWindow_drawCircleShape(manager->window,
            manager->tower_radius, NULL);
    }
}

static
void display_single_tower(manager_t *manager)
{
    if (manager->display_sprite == TRUE) {
        sfRenderWindow_drawSprite(manager->window,
            manager->tower_sprite, NULL);
    }
}

void display_tower(manager_t *manager, tower_t *tower)
{
    sfVector2f tower_position = { .x = 0, .y = 0 };
    sfVector2u size = { 0, 0 };

    for (int i = 0; i < manager->nb_towers; i += 1) {
        tower_position.x = tower[i].x_position;
        tower_position.y = tower[i].y_position;
        size = sfTexture_getSize(manager->tower_texture);
        sfSprite_setOrigin(manager->tower_sprite,
            (sfVector2f){ (float)size.x / 2, (float)size.y / 2 });
        sfSprite_setPosition(manager->tower_sprite, tower_position);
        tower_position.x -= tower[i].radius;
        tower_position.y -= tower[i].radius;
        display_area(manager, tower, i, tower_position);
        display_single_tower(manager);
    }
}
