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
#include "display.h"
#include "simulation_manager.h"
#include "plane_manager.h"
#include "tower_manager.h"
#include "collision.h"
#include "grid.h"

static
int free_array(manager_t *manager, aircraft_t **aircraft, tower_t **tower,
    int return_value)
{
    if (manager->grid != NULL)
        destroy_grid(manager);
    if (tower != NULL && *tower != NULL)
        free(*tower);
    if (aircraft != NULL && *aircraft != NULL)
        free(*aircraft);
    return return_value;
}

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
    if (sim_manager->background_texture != NULL)
        sfTexture_destroy(sim_manager->background_texture);
    if (sim_manager->background_sprite != NULL)
        sfSprite_destroy(sim_manager->background_sprite);
    if (sim_manager->hitbox != NULL)
        sfRectangleShape_destroy(sim_manager->hitbox);
    if (sim_manager->tower_radius != NULL)
        sfCircleShape_destroy(sim_manager->tower_radius);
    return free_array(sim_manager, aircraft, tower, return_value);
}

static
int load_sprite(manager_t *sim_manager)
{
    if (sim_manager->plane_sprite == NULL)
        return FAILURE;
    sfSprite_setTexture(sim_manager->plane_sprite, sim_manager->plane_texture,
                        sfTrue);
    sfSprite_setScale(sim_manager->plane_sprite, (sfVector2f){SCALE, SCALE});
    if (sim_manager->background_sprite == NULL)
        return FAILURE;
    sfSprite_setTexture(sim_manager->background_sprite,
                        sim_manager->background_texture, sfTrue);
    if (sim_manager->tower_sprite == NULL)
        return FAILURE;
    sfSprite_setTexture(sim_manager->tower_sprite, sim_manager->tower_texture,
                        sfTrue);
    sfSprite_setScale(sim_manager->tower_sprite, (sfVector2f){SCALE, SCALE});
    return SUCCESS;
}

static
void init_shape(manager_t *sim_manager)
{
    sfRectangleShape_setSize(sim_manager->hitbox, (sfVector2f){RECT, RECT});
    sfRectangleShape_setFillColor(sim_manager->hitbox, sfTransparent);
    sfRectangleShape_setOutlineThickness(sim_manager->hitbox, THICKNESS);
    sfRectangleShape_setOutlineColor(sim_manager->hitbox, sfGreen);
    sfCircleShape_setFillColor(sim_manager->tower_radius, sfTransparent);
    sfCircleShape_setOutlineThickness(sim_manager->tower_radius, THICKNESS);
    sfCircleShape_setOutlineColor(sim_manager->tower_radius, sfGreen);
}

static
int initialize_manager(manager_t *sim_manager)
{
    sfVideoMode mode = { WIDTH, HEIGHT, BPP };

    sim_manager->window = sfRenderWindow_create(mode, TITLE, sfClose, NULL);
    sim_manager->timer.microseconds = 0;
    sim_manager->plane_texture = sfTexture_createFromFile(PLANE, NULL);
    sim_manager->tower_texture = sfTexture_createFromFile(TOWER, NULL);
    sim_manager->background_texture = sfTexture_createFromFile(BACK, NULL);
    sim_manager->plane_sprite = sfSprite_create();
    sim_manager->tower_sprite = sfSprite_create();
    sim_manager->background_sprite = sfSprite_create();
    sim_manager->hitbox = sfRectangleShape_create();
    sim_manager->tower_radius = sfCircleShape_create();
    if (sim_manager->window == NULL || sim_manager->tower_texture == NULL ||
        sim_manager->plane_texture == NULL || sim_manager->hitbox == NULL ||
        sim_manager->background_texture == NULL)
        return display_error("Failed to load the assets\n");
    init_shape(sim_manager);
    sim_manager->grid = initialize_grid(sim_manager);
    return load_sprite(sim_manager);
}

static
void simulate(manager_t *manager, aircraft_t *aircraft, tower_t *tower,
    int *displayed)
{
    sfRenderWindow_clear(manager->window, sfBlack);
    display_background(manager);
    *displayed = display_plane(manager, aircraft);
    if (*displayed != 0) {
        display_tower(manager, tower);
        check_collision(manager, tower);
    }
}

static
void update_frame(manager_t *manager, aircraft_t *aircraft, tower_t *tower,
    sfClock *clock)
{
    sfTime time;
    int alive = 1;

    while (sfRenderWindow_isOpen(manager->window) && alive != 0) {
        time = sfClock_getElapsedTime(clock);
        if (sfRenderWindow_pollEvent(manager->window, &(manager->event)))
            check_events(manager);
        if (sfTime_asMilliseconds(time) >= TIME_FRAME_MS) {
            simulate(manager, aircraft, tower, &alive);
            display_ath(manager, clock);
            sfRenderWindow_display(manager->window);
            time = sfClock_getElapsedTime(clock);
            manager->timer.microseconds += time.microseconds;
            sfClock_restart(clock);
        }
    }
}

static
int simulation_loop(manager_t *manager, aircraft_t *aircraft, tower_t *tower)
{
    sfClock *clock = sfClock_create();

    if (clock == NULL)
        return FAILURE;
    sfRenderWindow_display(manager->window);
    update_frame(manager, aircraft, tower, clock);
    if (clock != NULL)
        sfClock_destroy(clock);
    return SUCCESS;
}

int my_radar(const char *path)
{
    int return_value = SUCCESS;
    manager_t sim_manager = { .window = NULL, .plane_texture = NULL,
        .tower_texture = NULL, .plane_sprite = NULL, .tower_sprite = NULL,
        .background_texture = NULL, .background_sprite = NULL, .hitbox = NULL,
        .tower_radius = NULL, .display_area = TRUE, .display_sprite = TRUE,
        .grid = NULL, .nb_planes = 0, .nb_towers = 0, .fps = 0.f };
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
