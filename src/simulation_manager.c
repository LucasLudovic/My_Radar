/*
** EPITECH PROJECT, 2023
** Simulation manager
** File description:
** loop for the my_radar project
*/

#include <SFML/Graphics.h>
#include <stddef.h>
#include <stdlib.h>
#include "load_entities.h"
#include "my.h"
#include "my_macros.h"
#include "my_structs.h"
#include "events.h"

static
int destroy_end(manager_t *sim_manager, aircraft_t **aircraft,
    tower_t **tower, int return_value)
{
    if (sim_manager->window != NULL)
        sfRenderWindow_destroy(sim_manager->window);
    if (sim_manager->plane_texture != NULL)
        sfTexture_destroy(sim_manager->plane_texture);
    if (sim_manager->tower_texture != NULL)
        sfTexture_destroy(sim_manager->tower_texture);
    if (sim_manager->plane_sprite != NULL)
        sfSprite_destroy(sim_manager->plane_sprite);
    if (sim_manager->tower_sprite != NULL)
        sfSprite_destroy(sim_manager->tower_sprite);
    if (tower != NULL && *tower != NULL)
        free(*tower);
    if (aircraft != NULL && *aircraft != NULL)
        free(*aircraft);
    return return_value;
}

static
int initialize_manager(manager_t *sim_manager)
{
    sfVideoMode mode = { WIDTH, HEIGHT, BPP };

    sim_manager->window = sfRenderWindow_create(mode, TITLE, sfClose, NULL);
    sim_manager->nb_planes = 0;
    sim_manager->nb_towers = 0;
    sim_manager->plane_texture = sfTexture_createFromFile(PLANE, NULL);
    sim_manager->tower_texture = sfTexture_createFromFile(TOWER, NULL);
    sim_manager->plane_sprite = sfSprite_create();
    sim_manager->tower_sprite = sfSprite_create();
    if (sim_manager->window == NULL || sim_manager->tower_texture == NULL ||
        sim_manager->plane_texture == NULL)
        return display_error("Failed to load the assets\n");
    sfSprite_setTexture(sim_manager->plane_sprite, sim_manager->plane_texture,
    sfTrue);
    sfSprite_setScale(sim_manager->plane_sprite, (sfVector2f){0.1, 0.1});
    return SUCCESS;
}

static
void simulate(manager_t *manager, aircraft_t *aircraft, tower_t *tower)
{
    sfVector2f plane_position = { .x = 100, .y = 100 };

    for (int i = 0; i < manager->nb_planes; i += 1) {
        plane_position.x = (float)aircraft[i].x_departure;
        plane_position.y = (float)aircraft[i].y_departure;
        sfSprite_setPosition(manager->plane_sprite, plane_position);
        sfRenderWindow_drawSprite(manager->window,
            manager->plane_sprite, NULL);
    }
    sfRenderWindow_display(manager->window);
}

static
int simulation_loop(manager_t *manager, aircraft_t *aircraft, tower_t *tower)
{
    int loop = sfTrue;
    sfClock *clock = sfClock_create();
    sfTime time;

    if (clock == NULL)
        return FAILURE;
    sfRenderWindow_display(manager->window);
    while (sfRenderWindow_isOpen(manager->window)) {
        time = sfClock_getElapsedTime(clock);
        if (sfRenderWindow_pollEvent(manager->window, &(manager->event)))
            check_events(manager);
        if (sfTime_asMilliseconds(time) >= 20) {
            simulate(manager, aircraft, tower);
            sfClock_restart(clock);
        }
    }
    if (clock != NULL)
        sfClock_destroy(clock);
    return SUCCESS;
}

int my_radar(const char *path)
{
    int return_value = SUCCESS;
    manager_t sim_manager = { .window = NULL, .plane_texture = NULL,
        .tower_texture = NULL, .plane_sprite = NULL, .tower_sprite = NULL,
        .nb_planes = 0, .nb_towers = 0, .display_area = 1, .display_sprite = 1 };
    aircraft_t *aircraft = NULL;
    tower_t *tower = NULL;

    return_value = initialize_manager(&sim_manager);
    if (return_value != FAILURE)
        return_value = allocate_memory(&aircraft, &tower, path, &sim_manager);
    if (return_value != FAILURE)
        return_value = add_planes_towers(&sim_manager, path, aircraft, tower);
    if (return_value != FAILURE) {
        sfRenderWindow_setFramerateLimit(sim_manager.window, FRAME);
        return_value = simulation_loop(&sim_manager, aircraft, tower);
    }
    return destroy_end(&sim_manager, &aircraft, &tower, return_value);
}
