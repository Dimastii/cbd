#include <stdio.h>
#include <math.h>
#include "mlx.h"
#include "fcntl.h"
#include "gnl/get_next_line.h"

typedef struct  s_vars {
	void        *mlx;
	void        *win;

	int size_win_w;
	int size_win_h;

	double x;
	double y;

	int key;

}               t_vars;


int             key_hook(int keycode, t_vars *vars)
{
	printf("k_code:! %d\n", keycode);
	if (keycode == 123)
		vars->x -= 0.2;
	if (keycode == 124)
		vars->x += 0.2;
	if (keycode == 125)
		vars->y += 0.2;
	if (keycode == 126)
		vars->y -= 0.2;
	mlx_pixel_put(vars->mlx, vars->win, vars->x, vars->y, 0x00FF0000);
}

void 	lets_pars(char *cub)
{
	int fd;
	char* line;
	fd = open(cub, O_RDONLY);
	get_next_line(fd, &line);
	printf("|%s|\n", line);
	free(line);
}

void rey(t_vars vars)
{
	double i = 0;

	int arr_test_stop_rey[3][3] = {{0, 0, 0},
								   {0, 1, 0},
								   {0, 0, 0}};
while (i++ < vars.size_win_w) {
	double player_a = 1.523;
	double angle = player_a - 90 / 2 + 90 * i / vars.size_win_w;
	double t = 0;
	while (t < 20) {
		t += 1;
		double cx = vars.x + t * cos(angle);
		double cy = vars.y + t * sin(angle);
		if (arr_test_stop_rey[(int)cx][(int)cy] == 0) break;
		mlx_pixel_put(vars.mlx, vars.win,(int)cx, (int)cy, 0x00FF0000);
	}
}
}

int             kek(int keycode, t_vars *vars)
{
		rey(*vars);
	if (vars->key == -1)
	{
		vars->key = keycode;
		key_hook(vars->key, vars);
	}
	else
		vars->key = -1;
	return (0);
}

int             main(void)
{
	t_vars      vars;
	vars.size_win_w = 640;
	vars.size_win_h = 480;

	int arr_test_stop_rey[3][3] = {{2, 0, 0},
								   {0, 1, 0},
								   {0, 0, 0}};

	vars.x = 1;
	vars.y = 1;
	vars.key = -1;
	vars.mlx = mlx_init();

	lets_pars("cub.cub");

	vars.win = mlx_new_window(vars.mlx, vars.size_win_w, vars.size_win_h, "Gucci flip flops");
	mlx_hook(vars.win, 2, 1L<<0, kek, &vars);


//	mlx_hook(vars.win, 3, 1L<<1, kek, &vars);

	//mlx_pixel_put(vars.mlx, vars.win, x, y, 0x00FF0000);
	mlx_loop(vars.mlx);
}