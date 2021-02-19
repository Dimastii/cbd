# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/23 17:34:28 by cveeta            #+#    #+#              #
#    Updated: 2021/02/18 15:50:05 by cveeta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cube3D.a
CC      = gcc
#CFLAGS  = -Wall -Wextra -Werror
RM	= rm -f
SRCS =	main.c preprocess.c general_utils.c render_wall_back.c save.c sprt.c utils.c \
		preprocess_map.c\

OBJ	= $(SRCS:.c=.o)
BONUS_OBJ	= $(BONUS:.c=.o)

all:	$(NAME)
$(NAME):$(OBJ)
		cd libft && make bonus && mv libft.a ../
		gcc $(SRCS) libmlx.dylib libft.a -o $(NAME)
clean:
		$(RM) $(OBJ) $(BONUS_OBJ)
fclean:	clean
		$(RM) $(NAME)
		cd libft && make clean
re:		fclean $(NAME)
bonus:	$(OBJ) $(BONUS_OBJ)
		ar rc $(NAME) $(OBJ) $(BONUS_OBJ) cub.h