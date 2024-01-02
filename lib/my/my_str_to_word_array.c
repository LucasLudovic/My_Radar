/*
** EPITECH PROJECT, 2023
** MY_STR_TO_WORD_ARRAY
** File description:
** Split a string into words
*/

#include <stdlib.h>
#include <stddef.h>

static
int my_isalphanum(char const str)
{
    int condition1 = str < 48 || str > 57;
    int condition2 = str < 65 || str > 90;
    int condition3 = str < 97 || str > 122;

    if (condition1 && condition2 && condition3)
        return 0;
    return 1;
}

static
int get_word_length(char const *str)
{
    int i = 0;
    int j = 0;

    while (1) {
        while (my_isalphanum(str[j])) {
            i += 1;
            j += 1;
        }
        if (i > 0)
            return i;
        j += 1;
    }
}

static
int get_nb_of_words(char const *str)
{
    int words = 0;
    int condition1 = 0;
    int condition2 = 0;

    for (int i = 1; str[i] != '\0'; i += 1) {
        condition1 = my_isalphanum(str[i]);
        condition2 = my_isalphanum(str[i - 1]);
        if (!condition1 && condition2)
            words += 1;
    }
    return words;
}

static
void divide_into_array(char **ptr_to_return, char *arr, int number_of_words)
{
    int word_length = 0;

    for (int i = 0; i < number_of_words; i += 1) {
        while (my_isalphanum(*arr) != 1)
            arr += 1;
        word_length = get_word_length(arr);
        ptr_to_return[i] = malloc(sizeof(char) * (word_length + 1));
        for (int j = 0; j < word_length; j += 1)
            ptr_to_return[i][j] = arr[j];
        ptr_to_return[i][word_length] = '\0';
        arr += word_length;
    }
}

char **my_str_to_word_array(char *tab)
{
    int number_of_words = get_nb_of_words(tab);
    char *arr = tab;
    char **ptr_to_return = malloc(sizeof(char *) * (number_of_words + 1));

    if (ptr_to_return == NULL)
        return NULL;
    if (arr == NULL) {
        free(ptr_to_return);
        return NULL;
    }
    divide_into_array(ptr_to_return, arr, number_of_words);
    ptr_to_return[number_of_words] = NULL;
    return ptr_to_return;
}
