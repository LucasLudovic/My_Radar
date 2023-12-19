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
int add_single_tower(void)
{
    return SUCCESS;
}

static
int add_single_plane(void)
{
    return SUCCESS;
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
