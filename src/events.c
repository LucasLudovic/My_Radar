/*
** EPITECH PROJECT, 2023
** Events
** File description:
** Check the events for the my_radar
*/

#include <SFML/Graphics.h>
#include <stdio.h>
#include "my_structs.h"
#include "my.h"

static
void switch_hitboxes_and_area(manager_t *manager)
{
    my_putstr("L\n");
}

static
void switch_sprites(manager_t *manager)
{
    my_putstr("S\n");
}

void check_events(manager_t *manager)
{
    if (manager->event.type == sfEvtClosed)
        sfRenderWindow_close(manager->window);
    if (sfKeyboard_isKeyPressed(sfKeyL) == sfTrue)
        switch_hitboxes_and_area(manager);
    if (sfKeyboard_isKeyPressed(sfKeyS) == sfTrue)
        switch_sprites(manager);
}
