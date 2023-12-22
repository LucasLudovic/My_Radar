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

void display_tower(manager_t *manager, tower_t *tower)
{
    sfVector2f tower_position = { .x = 0, .y = 0 };

    for (int i = 0; i < manager->nb_towers; i += 1) {
        tower_position.x = (float)tower[i].x_position;
        tower_position.y = (float)tower[i].y_position;
        sfSprite_setPosition(manager->tower_sprite, tower_position);
        if (manager->display_sprite == 1) {
            sfRenderWindow_drawSprite(manager->window,
                manager->tower_sprite, NULL);
        }
    }
}
