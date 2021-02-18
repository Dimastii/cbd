# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/23 17:34:28 by cveeta            #+#    #+#              #
#    Updated: 2021/02/18 12:17:17 by cveeta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SRC = main.c preprocess.c render_wall_back.c save.c sprt.c utils.c get_next_line/get_next_line.c \
#    get_next_line/get_next_line_utils.c
#OBJC = ${SRS:.c=.o}
#NAME = cube3D.a
#FLAG = -Wall -Wextra -Werror
#OBJC = ${SRC:.c=.o}
#GCC = gcc
#.c.o:
#    ${GCC} ${FLAG} -I. -c $< -o ${<:.c=.o}
#all: ${NAME}
#${NAME}: ${OBJC} libmlx.dylib
#    ar rc ${NAME} ${OBJC}
#bonus: all
#clean:
#    rm -f ${OBJC}
#fclean: clean
#    rm -f ${NAME}
#re: fclean all
#.PHONY: all clean fclean re bonus

NAME	= cube3D.a
CC      = gcc
#CFLAGS  = -Wall -Wextra -Werror
RM	= rm -f
SRCS = main.c preprocess.c render_wall_back.c save.c sprt.c utils.c get_next_line.c \
    get_next_line_utils.c
OBJ	= $(SRCS:.c=.o)
BONUS_OBJ	= $(BONUS:.c=.o)
all:	$(NAME)
$(NAME):$(OBJ) libmlx.dylib
		ar rc $(NAME) $(OBJ) cub.h
clean:
		$(RM) $(OBJ) $(BONUS_OBJ)
fclean:	clean
		$(RM) $(NAME)
re:		fclean $(NAME)
bonus:	$(OBJ) $(BONUS_OBJ)
		ar rc $(NAME) $(OBJ) $(BONUS_OBJ) cub.h