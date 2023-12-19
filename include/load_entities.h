/*
** EPITECH PROJECT, 2023
** Load Entities
** File description:
** Header for loading the entities
*/

#ifndef ENTITIES_H_
    #define ENTITIES_H_
    #include <stdio.h>
    #include "my_structs.h"

int allocate_memory(aircraft_t **aircraft, tower_t **tower,
    const char *path, manager_t *manager);
int add_planes_towers(manager_t *manager, const char *path,
    aircraft_t *aircraft, tower_t *tower);
int check_nb_assets(manager_t *manager, char *buff, FILE *file);

#endif
