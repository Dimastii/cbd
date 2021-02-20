cmake_minimum_required(VERSION 3.17)
project(cub3D)

set(CMAKE_CXX_STANDARD 99)
set(CMAKE_C_FLAGS "-lmlx -framework OpenGL -framework AppKit")
include_directories(minilibx_mms_20200219)
include_directories(libft)
link_directories(./)

add_executable(cub3D
		minilibx_mms_20200219/mlx.h
		libft/get_next_line.h
		libft/get_next_line.c
		libft/get_next_line_utils.c
		libmlx.dylib
		main.c
		sprt.c
		cub.h
		render_wall_back.c general_utils.c preprocess.c utils.c save.c preprocess_map.c
		map_valid.c utils2.c main_check_argv_and_init.c game_loop.c conditions_for_sprt.c hook_move.c)
