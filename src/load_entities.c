/*
** EPITECH PROJECT, 2023
** Load entities
** File description:
** Load the entities for the my_radar project
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "my_macros.h"
#include "my_structs.h"
#include "simulation_manager.h"
#include "load_entities.h"

static
int add_to_tower(tower_t *tower, char **array, int tower_added)
{
    for (int i = 0; i < DATA_TOWER; i += 1)
        if (array[i] == NULL)
            return FAILURE;
    if (array[DATA_TOWER] != NULL)
        return FAILURE;
    tower[tower_added].x_position = (float)my_getnbr(array[1]);
    tower[tower_added].y_position = (float)my_getnbr(array[2]);
    tower[tower_added].radius = (float)my_getnbr(array[3]);
    tower[tower_added].radius *= (float)WIDTH;
    tower[tower_added].radius /= 100.f;
    if (my_getnbr(array[1]) > WIDTH || my_getnbr(array[1]) < 0 ||
        my_getnbr(array[2]) > HEIGHT || my_getnbr(array[2]) < 0 ||
        my_getnbr(array[3]) > 100 || my_getnbr(array[3]) < 0)
        return FAILURE;
    return SUCCESS;
}

static
int add_single_tower(manager_t *manager, tower_t *tower, char *buff)
{
    static int tower_added = 0;
    char **array_of_words = NULL;
    int return_value = SUCCESS;

    if (buff == NULL || manager == NULL || tower == NULL)
        return FAILURE;
    if (tower_added == manager->nb_towers)
        return FAILURE;
    array_of_words = my_str_to_word_array(buff);
    if (array_of_words == NULL || *array_of_words == NULL)
        return FAILURE;
    return_value = add_to_tower(tower, array_of_words, tower_added);
    tower_added += 1;
    return return_value;
}

static
void add_positions(aircraft_t *aircraft, char **array, int plane_added)
{
    aircraft[plane_added].x_departure = (float)my_getnbr(array[1]);
    aircraft[plane_added].y_departure = (float)my_getnbr(array[2]);
    aircraft[plane_added].x_current = aircraft[plane_added].x_departure;
    aircraft[plane_added].y_current = aircraft[plane_added].y_departure;
    aircraft[plane_added].x_arrival = (float)my_getnbr(array[3]);
    aircraft[plane_added].y_arrival = (float)my_getnbr(array[4]);
}

static
int add_to_plane(aircraft_t *aircraft, char **array, int plane_added)
{
    for (int i = 0; i < DATA_PLANE; i += 1)
        if (array[i] == NULL)
            return FAILURE;
    if (array[DATA_PLANE] != NULL)
        return FAILURE;
    add_positions(aircraft, array, plane_added);
    aircraft[plane_added].speed = (float)my_getnbr(array[5]);
    aircraft[plane_added].delay = (float)my_getnbr(array[6]);
    aircraft[plane_added].arrived = FALSE;
    aircraft[plane_added].destroyed = FALSE;
    aircraft[plane_added].invincible = FALSE;
    if (aircraft[plane_added].x_departure > (float)WIDTH ||
        aircraft[plane_added].x_arrival > (float)WIDTH ||
        aircraft[plane_added].y_departure > (float)HEIGHT ||
        aircraft[plane_added].y_arrival > (float)HEIGHT)
        return FAILURE;
    return SUCCESS;
}

static
int add_single_plane(manager_t *manager, aircraft_t *aircraft, char *buff)
{
    static int plane_added = 0;
    char **array_of_words = NULL;
    int return_value = SUCCESS;

    if (buff == NULL || manager == NULL || aircraft == NULL)
        return FAILURE;
    if (plane_added == manager->nb_planes)
        return FAILURE;
    array_of_words = my_str_to_word_array(buff);
    if (array_of_words == NULL || *array_of_words == NULL)
        return FAILURE;
    return_value = add_to_plane(aircraft, array_of_words, plane_added);
    plane_added += 1;
    return return_value;
}

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
int check_entities(char *buff, manager_t *manager, aircraft_t *aircraft,
    tower_t *tower)
{
    if (buff[0] == 'A')
        if (add_single_plane(manager, aircraft, buff) == FAILURE)
            return display_error("Wrong value in file (plane)\n");
    if (buff[0] == 'T')
        if (add_single_tower(manager, tower, buff))
            return display_error("Wrong value in file (tower)\n");
    return SUCCESS;
}

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
        if (end_file <= 0)
            break;
        if (check_entities(buff, manager, aircraft, tower) == FAILURE)
            return FAILURE;
    }
    if (buff != NULL)
        free(buff);
    return SUCCESS;
}

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
    return SUCCESS;
}
