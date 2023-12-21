/*
** EPITECH PROJECT, 2023
** Events
** File description:
** Check the events for the my_radar
*/

#include <SFML/Graphics.h>
#include "my_macros.h"
#include "my_structs.h"
#include "display.h"

int display_background(manager_t *manager)
{
    sfRenderWindow_drawSprite(manager->window, manager->background_sprite,
        NULL);
    return SUCCESS;
}
