/*
** EPITECH PROJECT, 2023
** Events
** File description:
** Check the events for the my_radar
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "my_macros.h"
#include "my_structs.h"
#include "display.h"

int display_background(manager_t *manager)
{
    sfRenderWindow_drawSprite(manager->window, manager->background_sprite,
        NULL);
    return SUCCESS;
}

static
void *destroy_time(sim_timer_t *sim_timer)
{
    if (sim_timer->hours_str != NULL)
        free(sim_timer->hours_str);
    if (sim_timer->minutes_str != NULL)
        free(sim_timer->minutes_str);
    if (sim_timer->seconds_str != NULL)
        free(sim_timer->seconds_str);
    return NULL;
}

static
void add_hours(sim_timer_t *sim_timer, char *timer_str)
{
    if (sim_timer->hours > 9) {
        timer_str[0] = sim_timer->hours_str[0];
        timer_str[1] = sim_timer->hours_str[1];
    } else {
        timer_str[0] = '0';
        timer_str[1] = sim_timer->hours_str[0];
    }
}

static
void add_to_str(char *timer_str, sim_timer_t *sim_timer)
{
    add_hours(sim_timer, timer_str);
    if (sim_timer->minutes > 9) {
        timer_str[3] = sim_timer->minutes_str[0];
        timer_str[4] = sim_timer->minutes_str[1];
    } else {
        timer_str[3] = '0';
        timer_str[4] = sim_timer->minutes_str[0];
    }
    if (sim_timer->seconds > 9) {
        timer_str[6] = sim_timer->seconds_str[0];
        timer_str[7] = sim_timer->seconds_str[1];
    } else {
        timer_str[6] = '0';
        timer_str[7] = sim_timer->seconds_str[0];
    }
}

static
void update_timer(sim_timer_t *sim_timer, char *timer_str)
{
    add_to_str(timer_str, sim_timer);
    timer_str[2] = ':';
    timer_str[5] = ':';
    timer_str[8] = '\0';
    destroy_time(sim_timer);
}

static
char *convert_time_to_text(manager_t *manager, char *timer_str)
{
    sim_timer_t sim_timer = { 0, 0, 0, NULL, NULL, NULL};

    if (timer_str == NULL)
        timer_str = malloc(sizeof(char) * CHARACTER_TIME);
    if (timer_str == NULL)
        return NULL;
    sim_timer.seconds = (int)sfTime_asSeconds(manager->timer) % 60;
    sim_timer.minutes = (int)(sfTime_asSeconds(manager->timer) / 60) % 60;
    sim_timer.hours = (int)(sfTime_asSeconds(manager->timer) / 3600);
    if (sim_timer.hours > 99)
        sim_timer.hours = 0;
    sim_timer.seconds_str = my_nbr_to_str(sim_timer.seconds);
    sim_timer.minutes_str = my_nbr_to_str(sim_timer.minutes);
    sim_timer.hours_str = my_nbr_to_str(sim_timer.hours);
    if (sim_timer.seconds_str == NULL || sim_timer.minutes_str == NULL ||
        sim_timer.hours_str == NULL)
        return destroy_time(&sim_timer);
    update_timer(&sim_timer, timer_str);
    return timer_str;
}

static
void draw_ath_element(sfText *time_text, sfFont *font,
    char *timer_str, sfVector2i position)
{
    sfVector2f position_float = { (float)position.x, (float)position.y };

    sfText_setPosition(time_text, position_float);
    sfText_setFont(time_text, font);
    sfText_setString(time_text, timer_str);
}

static
void display_timer(manager_t *manager, sfFont *font)
{
    sfText *time_text = NULL;
    char *timer_str = NULL;

    if (font == NULL)
        return;
    time_text = sfText_create();
    if (time_text == NULL)
        return;
    timer_str = convert_time_to_text(manager, timer_str);
    if (timer_str == NULL) {
        sfText_destroy(time_text);
        return;
    }
    draw_ath_element(time_text, font, timer_str, (sfVector2i){X_TIMER, 0});
    sfRenderWindow_drawText(manager->window, time_text, NULL);
    if (timer_str != NULL)
        free(timer_str);
    if (time_text != NULL)
        sfText_destroy(time_text);
}

static
void display_framerate(manager_t *manager, sfClock *clock, sfFont *font)
{
    sfText *frame_text = NULL;
    char *frame_str = NULL;

    if (font == NULL)
        return;
    frame_text = sfText_create();
    if (frame_text == NULL)
        return;
    manager->fps = 1 / (sfTime_asSeconds(sfClock_getElapsedTime(clock)));
    frame_str = my_nbr_to_str((int)manager->fps);
    if (frame_str == NULL) {
        sfText_destroy(frame_text);
        return;
    }
    draw_ath_element(frame_text, font, frame_str, (sfVector2i){ 0, 0 });
    sfRenderWindow_drawText(manager->window, frame_text, NULL);
    free(frame_str);
    sfText_destroy(frame_text);
}

void display_ath(manager_t *manager, sfClock *clock)
{
    sfFont *font = sfFont_createFromFile(FONT);

    display_timer(manager, font);
    if (clock != NULL)
        display_framerate(manager, clock, font);
    if (font != NULL)
        sfFont_destroy(font);
}
