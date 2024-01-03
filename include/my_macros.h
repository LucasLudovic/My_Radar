/*
** EPITECH PROJECT, 2023
** my_macros
** File description:
** Macros for the my_radar project
*/

#ifndef MY_MACROS_H_
    #define MY_MACROS_H_
    #define UNUSED __attribute__((unused))
    #define WIDTH 1980
    #define HEIGHT 1080
    #define BPP 32
    #define CHARACTER_TIME 9
    #define FONT "Ressources/arial.ttf"
    #define TITLE "Radar"
    #define PLANE "Ressources/Plane.png"
    #define TOWER "Ressources/Tower.png"
    #define BACK "Ressources/Background.jpg"
    #define FAILURE 84
    #define SUCCESS 0
    #define FRAME 60
    #define DATA_PLANE 7
    #define DATA_TOWER 4
    #define SPRITE_SIZE 20
    #define RECT 20.f
    #define THICKNESS 3.f
    #define SCALE 0.07f
    #define TIME_FRAME_MS 20
    #define SECOND_IN_MS 1000
    #define TRUE 1
    #define FALSE 0
    #define GRID_WIDTH (WIDTH / SPRITE_SIZE)
    #define GRID_HEIGHT (HEIGHT / SPRITE_SIZE)
#endif
