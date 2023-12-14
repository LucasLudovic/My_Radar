/*
** EPITECH PROJECT, 2023
** Main
** File description:
** Main for the my_radar project
*/

#include <SFML/Graphics.h>
#include <unistd.h>
#include <fcntl.h>
#include "my_macros.h"
#include "my.h"
#include "simulation_manager.h"

static
int check_env(UNUSED char **env)
{
    return SUCCESS;
}

int main(int argc, char **argv, char **env)
{
    int file = 0;

    if (check_env(env) != SUCCESS)
        return display_error("Unable to load the env\n");
    if (argc != 2)
        return display_error("Wrong number of arguments\n");
    file = open(argv[1], O_RDONLY);
    if (file <= 0)
        return display_error("Wrong file entered\n");
    close(file);
    return my_radar(argv[1]);
}
