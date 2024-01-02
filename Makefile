##
## EPITECH PROJECT, 2023
## MAKEFILE
## File description:
## Makefile for my lib
##

SRC	=	src/collision.c \
		src/display.c \
		src/events.c \
		src/grid.c \
		src/load_entities.c \
		src/main.c \
		src/plane_manager.c \
		src/simulation_manager.c \
		src/tower_manager.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_radar

CC	=	gcc

CFLAGS	=	-I include
CFLAGS	+=	-lcsfml-graphics
CFLAGS	+=	-lcsfml-audio
CFLAGS	+=	-lcsfml-window
CFLAGS	+=	-lcsfml-system
CFLAGS	+=	-W -Wall -Wextra -Wpedantic
CFLAGS	+=	-lm

LIB	=	-L lib/my -lmy

all:	$(NAME)

$(NAME):	$(OBJ)
	@make -C lib/my
	@make clean -C lib/my
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIB)
clean:
	@rm -f $(OBJ)

fclean:	clean
	@make fclean -C lib/my
	@rm -f $(NAME)

re: fclean all

.PHONY:	clean fclean re all
