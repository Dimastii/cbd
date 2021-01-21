#include <stdio.h>
#include <math.h>
#include "mlx.h"
#include "fcntl.h"
#include "gnl/get_next_line.h"

#define PI 3.14159265359

typedef struct  s_data {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

typedef struct  s_vars {
	void        *mlx;
	void        *win;

	int size_win_w;
	int size_win_h;

	double x;
	double y;

	double angle;

	int key;

	t_data 		img;
}               t_vars;


void rey(t_vars vars);

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int             key_hook(int keycode, t_vars *vars)
{
	double step;

	step = 10;
	rey(*vars);
	printf("k_code:! %d\n", keycode);
	if (keycode == 123) {
		printf("\nhere1\n");
		vars->x -= step;
	}
	if (keycode == 124) {
		printf("\nhere2\n");
		vars->x += step;
	}
	if (keycode == 125) {
		printf("\nhere3\n");
		vars->y += step;
	}
	if (keycode == 126) {
		printf("\nhere4\n");
		vars->y -= step;
	}
	if (keycode == 12) {
		printf("\nhere4\n");
		vars->angle += 0.05;
	}
}
void 	write_map(int arr[3][3],t_vars* vars)
{
	int x = 0;
	int y = 0;
	int i = 0;
	int j = 0;
	int scale = 300;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			x = 0;
			while (x <= scale)
			{
				y = 0;
				while (y <= scale)
				{
					if (arr[i][j] == 1)
						my_mlx_pixel_put(&(vars->img), i * scale + x, j * scale + y, 123123123);
					else
						my_mlx_pixel_put(&(vars->img), i * scale + x, j * scale + y, 321312321);
					y++;

				}

				x++;
			}
			//color += 100000;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}
void rey(t_vars vars)
{
	double i = 0;
	double cx = vars.x;
	double cy = vars.y;
	int color = 999999999;
	mlx_clear_window(vars.mlx, vars.win);
	int arr_test_stop_rey[3][3] = {{1, 1, 1},
								   {1, 0, 1},
								   {1, 1, 1}};
	//write_map(arr_test_stop_rey, &vars);

		double t = 0;
		while ( /*arr_test_stop_rey[(int) cx][(int) cy] != 1*/cx <= vars.size_win_w && cy <= vars.size_win_h && cx >= 0 && cy >= 0 ) {
			t += 0.05;
			cx = vars.x + t * cos(vars.angle);
			cy = vars.y + t * sin(vars.angle);
			if (arr_test_stop_rey[(int) cx / 300][(int) cy / 300] == 0){break;}
			my_mlx_pixel_put(&vars.img, (int)cx, (int)cy , color);
			color -=1000000;
		}
	my_mlx_pixel_put(&vars.img,vars.x , vars.y  , 0x0000FF00);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);

}

int             main(void)
{
	t_vars      vars;

	vars.size_win_w = 1000;
	vars.size_win_h = 1000;

	vars.x = 0;
	vars.y = 1.5;
	vars.key = -1;

	vars.angle = 0;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.size_win_w, vars.size_win_h, "Gucci flip flops");
	vars.img.img = mlx_new_image(vars.mlx, vars.size_win_w, vars.size_win_h);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);

	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_clear_window(vars.mlx, vars.win);
	mlx_hook(vars.win, 2, 1L<<0,key_hook , &vars);

	mlx_loop(vars.mlx);
}