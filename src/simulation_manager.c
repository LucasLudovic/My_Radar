/*
** EPITECH PROJECT, 2023
** Simulation manager
** File description:
** loop for the my_radar project
*/

#include <SFML/Graphics.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "my.h"
#include "my_macros.h"
#include "my_structs.h"
#include "events.h"

static
int destroy_end(manager_t *sim_manager, int return_value)
{
    if (sim_manager->window != NULL)
        sfRenderWindow_destroy(sim_manager->window);
    if (sim_manager->plane_texture != NULL)
        sfTexture_destroy(sim_manager->plane_texture);
    if (sim_manager->tower_texture != NULL)
        sfTexture_destroy(sim_manager->tower_texture);
    return return_value;
}

static
int initialize_manager(manager_t *sim_manager)
{
    sfVideoMode mode = { WIDTH, HEIGHT, BPP };

    sim_manager->window = sfRenderWindow_create(mode, TITLE, sfClose, NULL);
    sim_manager->tower_texture = sfTexture_createFromFile(TOWER, NULL);
    sim_manager->plane_texture = sfTexture_createFromFile(PLANE, NULL);
    sim_manager->nb_planes = 0;
    sim_manager->nb_towers = 0;
    if (sim_manager->window == NULL ||
        sim_manager->tower_texture == NULL ||
        sim_manager->plane_texture == NULL)
        return display_error("Failed to load the assets\n");
    return SUCCESS;
}

static
int simulation_loop(manager_t *manager)
{
    int loop = sfTrue;
    sfClock *clock = sfClock_create();
    sfTime time;

    if (clock == NULL)
        return FAILURE;
    sfRenderWindow_display(manager->window);
    while (sfRenderWindow_isOpen(manager->window)) {
        time = sfClock_getElapsedTime(clock);
        while (sfRenderWindow_pollEvent(manager->window, &(manager->event)))
            continue;
        if (sfTime_asMilliseconds(time) >= 20) {
            check_events(manager);
            sfClock_restart(clock);
        }
    }
    if (clock != NULL)
        sfClock_destroy(clock);
    return SUCCESS;
}

static
int check_nb_assets(manager_t *manager, char *buff, FILE *file)
{
    ssize_t end_file = 1;
    size_t len_read = 0;

    while (end_file > 0) {
        end_file = getline(&buff, &len_read, file);
        if (end_file <= 0)
            break;
        if (buff[0] == 'A')
            manager->nb_planes += 1;
        if (buff[0] == 'T')
            manager->nb_towers += 1;
        if (buff[0] != 'A' && buff[0] != 'T')
            return FAILURE;
    }
}

static
int allocate_memory(aircraft_t **aircraft, tower_t **tower,
    const char *path, manager_t *manager)
{
    FILE *file = fopen(path, "r");
    char *buff = NULL;

    if (file == NULL || aircraft == NULL || tower == NULL)
        return FAILURE;
    check_nb_assets(manager, buff, file);
    *aircraft = malloc(sizeof(aircraft_t) * manager->nb_planes);
    *tower = malloc(sizeof(tower_t) * manager->nb_towers);
    if (buff != NULL)
        free(buff);
    fclose(file);
    return SUCCESS;
}

static
int add_single_tower(void)
{
    return SUCCESS;
}

static
int add_single_plane(void)
{
    return SUCCESS;
}

static
int add_planes_towers(manager_t *manager, const char *path,
    aircraft_t *aircraft, tower_t *tower)
{
    FILE *file = fopen(path, "r");
    char *buff = NULL;
    size_t len_read = 0;
    ssize_t end_file = 1;

    if (file == NULL || aircraft == NULL || tower == NULL)
        return FAILURE;
    while (end_file > 0) {
        end_file = getline(&buff, &len_read, file);
        if (end_file == 'A') {
            add_single_plane();
            continue;
        }
        if (end_file == 'T') {
            add_single_tower();
            continue;
        }
    }
    if (buff != NULL)
        free(buff);
}

int my_radar(const char *path)
{
    int return_value = SUCCESS;
    manager_t sim_manager = { .window = NULL, .plane_texture = NULL,
        .tower_texture = NULL, .nb_planes = 0, .nb_towers = 0 };
    aircraft_t *aircraft = NULL;
    tower_t *tower = NULL;

    return_value = initialize_manager(&sim_manager);
    if (return_value != FAILURE)
        return_value = allocate_memory(&aircraft, &tower, path, &sim_manager);
    if (return_value != FAILURE)
        return_value = add_planes_towers(&sim_manager, path, aircraft, tower);
    if (return_value != FAILURE) {
        sfRenderWindow_setFramerateLimit(sim_manager.window, FRAME);
        return_value = simulation_loop(&sim_manager);
    }
    return destroy_end(&sim_manager, return_value);
}
