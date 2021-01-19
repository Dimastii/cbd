# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/23 17:34:28 by cveeta            #+#    #+#              #
#    Updated: 2020/12/24 18:42:01 by cveeta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= a
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror

LFLAGS	=
RM	= rm -f
SRCS	=	main.c
OBJ	= %.o: %.c\
          $(CC) $(CFLAGS) -c $< -o $@
BONUS_OBJ	= $(BONUS:.c=.o)

all:	$(NAME)
$(NAME): $(OBJ)
    $(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
		$(RM) $(OBJ) $(BONUS_OBJ)
fclean:	clean
		$(RM) $(NAME)
re:		fclean $(NAME)
bonus:	$(OBJ) $(BONUS_OBJ)
		ar rc $(NAME) $(OBJ) $(BONUS_OBJ) ft_printf.h


#SRC = $(shell find . -name "ft_*.c") get_next_line/get_next_line.c \
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