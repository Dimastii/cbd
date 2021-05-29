# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/23 17:34:28 by cveeta            #+#    #+#              #
#    Updated: 2021/02/21 11:50:48 by cveeta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror
RM		= rm -f
SRCS 	=	main.c preprocess.c general_utils.c render_wall_back.c save.c sprt.c utils.c \
		preprocess_map.c\
        map_valid0.c utils2.c main_check_argv_and_init.c game_loop.c conditions_for_sprt.c hook_move.c map_valid1.c map_valid2.c preprocess_rgb.c preprocess_cardinal_points.c

OBJ		= $(SRCS:.c=.o)
BONUS_OBJ	= $(BONUS:.c=.o)

all:	$(NAME)
$(NAME):$(OBJ)
		cd lb && make bonus && mv libft.a ../
		gcc $(SRCS) libmlx.dylib libft.a -o $(NAME)
clean:
		$(RM) $(OBJ) $(BONUS_OBJ)
fclean:	clean
		$(RM) $(NAME)
		cd lb && make fclean
re:		fclean all
bonus:	$(OBJ) $(BONUS_OBJ)
		ar rc $(NAME) $(OBJ) $(BONUS_OBJ) cub.h