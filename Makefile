##
## EPITECH PROJECT, 2023
## MAKEFILE
## File description:
## Makefile for my lib
##

SRC	=	$(wildcard src/*.c)

OBJ	=	$(SRC:.c=.o)

NAME	=	my_radar

CC	=	gcc

CFLAGS	=	-I include
CFLAGS	+=	-lcsfml-graphics
CFLAGS	+=	-lcsfml-audio
CFLAGS	+=	-lcsfml-window
CFLAGS	+=	-lcsfml-system

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
