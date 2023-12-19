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
    tower[tower_added].x_position = my_getnbr(array[1]);
    tower[tower_added].y_position = my_getnbr(array[2]);
    tower[tower_added].radius = my_getnbr(array[3]);
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
int add_to_plane(aircraft_t *aircraft, char **array, int plane_added)
{
    for (int i = 0; i < DATA_PLANE; i += 1)
        if (array[i] == NULL)
            return FAILURE;
    if (array[DATA_PLANE] != NULL)
        return FAILURE;
    aircraft[plane_added].x_departure = my_getnbr(array[1]);
    aircraft[plane_added].y_departure = my_getnbr(array[1]);
    aircraft[plane_added].x_arrival = my_getnbr(array[1]);
    aircraft[plane_added].y_arrival = my_getnbr(array[1]);
    aircraft[plane_added].speed = my_getnbr(array[1]);
    aircraft[plane_added].delay = my_getnbr(array[1]);
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
        if (buff[0] == 'A')
            add_single_plane(manager, aircraft, buff);
        if (buff[0] == 'T')
            add_single_tower(manager, tower, buff);
    }
    if (buff != NULL)
        free(buff);
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
