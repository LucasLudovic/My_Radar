##
## EPITECH PROJECT, 2023
## MAKEFILE
## File description:
## Makefile for my lib
##

SRC	=	collision.c \
		../src/display.c \
		../src/events.c \
		../src/grid.c \
		../src/load_entities.c \
		../src/main.c \
		plane_manager.c \
		simulation_manager.c \
		../src/tower_manager.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_radar

CC	=	gcc -g

CFLAGS	=	-I ../include
CFLAGS	+=	-lcsfml-graphics
CFLAGS	+=	-lcsfml-audio
CFLAGS	+=	-lcsfml-window
CFLAGS	+=	-lcsfml-system
CFLAGS	+=	-W -Wall -Wextra -Wpedantic
CFLAGS	+=	-lm

LIB	=	-L ../lib/my -lmy

all:	$(NAME)

$(NAME):	$(OBJ)
	@make -C ../lib/my
	@make clean -C ../lib/my
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIB)
	@mv my_radar ../

clean:
	@rm -f $(OBJ)

fclean:	clean
	@make fclean -C ../lib/my
	@rm -f $(NAME)

re: fclean all

.PHONY:	clean fclean re all
