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
int display_help(void)
{
    my_putstr("Air traffic simulation panel\n");
    my_putstr("USAGE\n");
    my_putstr("\t./my_radar path_to_script\n");
    my_putstr("\tpath_to_script The path to the script file.\n");
    my_putstr("OPTIONS\n");
    my_putstr("\t-h print the usage and quit.\n");
    my_putstr("USER INTERACTIONS\n");
    my_putstr("\t‘L’ key enable/disable hitboxes and areas.\n");
    my_putstr("\t‘S’ key enable/disable sprites.");
    return SUCCESS;
}

static
int check_env(UNUSED char **env)
{
    int env_found = 0;

    for (int i = 0; env[i] != NULL; i += 1) {
        if (my_strncmp(env[i], "DISPLAY=", 8) == 0)
            env_found += 1;
        if (my_strncmp(env[i], "XAUTHORITY=", 11) == 0)
            env_found += 1;
    }
    if (env_found != 2)
        return display_error("Can't open a graphical program\n");
    return SUCCESS;
}

int main(int argc, char **argv, char **env)
{
    int file = 0;

    if (check_env(env) != SUCCESS)
        return display_error("Unable to load the env\n");
    if (argv == NULL)
        return FAILURE;
    if (argc != 2)
        return display_error("Wrong number of arguments\n");
    if (my_strcmp(argv[1], "-h") == 0)
        return display_help();
    file = open(argv[1], O_RDONLY);
    if (file <= 0)
        return display_error("Wrong file entered\n");
    close(file);
    return my_radar(argv[1]);
}
