/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 21:40:42 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/20 22:24:10 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int				main(int argc, char **argv)
{
	t_vars	vars;

	check_argv(&vars, argc, argv);
	open_file(&vars, argv[1]);
	init_mlx(&vars);
	if (vars.mode_gl == 1)
		mlx_hook(vars.win, 2, 1L << 0, key_hook, &vars);
	if (vars.mode_gl == 1)
		mlx_hook(vars.win, 3, 1L << 1, key_release_hook, &vars);
	mlx_loop_hook(vars.mlx, game_loop, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
