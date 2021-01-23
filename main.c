#include <stdio.h>
#include <math.h>
#include "mlx.h"
#include "fcntl.h"
#include "gnl/get_next_line.h"

#define PI 3.14159265359
#define ANLGLE PI / 2

#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
		{
				{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
				{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
				{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
				{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
				{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
				{4,0,0,0,0,0,0,5,5,0,5,5,5,5,5,5,0,7,0,7,7,7,7,7},
				{4,0,0,0,0,0,0,5,0,0,0,5,0,5,0,5,0,0,0,0,7,7,7,1},
				{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,8},
				{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
				{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,8},
				{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,0,0,7,7,7,1},
				{4,0,0,0,0,0,0,5,5,0,5,0,5,5,5,5,0,7,7,7,7,7,7,1},
				{6,6,0,6,0,6,0,6,6,0,6,0,6,6,6,6,0,6,6,6,6,6,6,6},
				{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
				{6,6,0,6,0,6,0,6,6,0,6,0,6,6,6,6,0,6,6,6,6,6,6,6},
				{4,4,0,4,0,4,0,4,4,0,6,0,6,2,2,2,0,2,2,2,3,3,3,3},
				{4,0,0,0,0,0,0,0,0,0,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
				{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,0,0,0,2,0,0,0,2},
				{4,0,0,0,0,0,0,0,0,0,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
				{4,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,2},
				{4,0,0,5,0,0,0,0,0,0,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
				{4,0,0,0,0,0,0,0,0,0,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
				{4,0,0,0,0,0,0,0,0,0,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
				{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
		};


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


void rey(t_vars* vars);

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}



int             key_hook(int keycode, t_vars *vars)
{
	double step;
	double turn;

	step = 9;
	turn = 0.09;
	printf("k_code:! %d\n", keycode);
	if (keycode == 123) {
		vars->x -= step;
	}
	if (keycode == 124) {
		vars->x += step;
	}
	if (keycode == 125) {
		vars->y += step;
	}
	if (keycode == 126) {
		vars->y -= step;
	}
	if (keycode == 12) {
		vars->angle += turn;
	}
	if (keycode == 14) {
		vars->angle -= turn;
	}
	//rey(vars);
}

void	write_map(t_vars* vars)
{
	int i = mapWidth;
	int j = mapHeight;
	int sc = vars->size_win_w / mapWidth;
	while (i--)
	{
		j = mapHeight;
		while (j--) {
			if (worldMap[j][i] == 0) {
				sc = vars->size_win_w / mapWidth;
				while (sc-- != 0) {

					my_mlx_pixel_put(&vars->img, (int) (j * (vars->size_win_h / mapHeight) + sc),
									 (int) (i * (vars->size_win_w / mapWidth) + sc), 0x8800FF00);
				}
			}
		}
	}
}

unsigned long colorr = 0xFFFFF0;

void rey(t_vars* vars)
{
	double cx;
	double cy;

	mlx_destroy_image(vars->mlx, vars->img.img);
	vars->img.img = mlx_new_image(vars->mlx, vars->size_win_w, vars->size_win_h);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	write_map(vars);
	double t;
	double angle_offset = ANLGLE / 512;
	double qqq = vars->angle * 1.5;
	double angle = qqq;
	while (angle <= qqq + ANLGLE)
	{
		//printf("123123123\n");
		t = 0;
		cx = vars->x;
		cy = vars->y;
		while (cx <= vars->size_win_w && cy < vars->size_win_h - 1 && cx >= 0 && cy >= 0) {
			t += 2;
			colorr -= 10;
			cx = vars->x + t * cos(angle);
			cy = vars->y + t * sin(angle);
			if (worldMap[(int) cx / (vars->size_win_w / mapWidth)][(int) cy / (vars->size_win_h / mapHeight)] != 0) { break; }
			my_mlx_pixel_put(&vars->img, (int) cx, (int) cy, 0x20FFF000);
		}
		//	my_mlx_pixel_put(&vars->img, n, n, 0x000000FF);
		//printf("%d\n", n);

		angle += angle_offset;
	}
	//printf("%d\n", n);
	//printf("123123123\n");
	my_mlx_pixel_put(&vars->img,vars->x , vars->y  , 0x00FF0000);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);

}

int             main(void)
{
	t_vars      vars;

	vars.size_win_w = 1000;
	vars.size_win_h = 1000;

	vars.x = 50;
	vars.y = 50;
	vars.key = -1;

	vars.angle = 0;

	vars.mlx = mlx_init();

	vars.win = mlx_new_window(vars.mlx, vars.size_win_w, vars.size_win_h, "Gucci flip flops");
	vars.img.img = mlx_new_image(vars.mlx, vars.size_win_w, vars.size_win_h);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);

	mlx_hook(vars.win, 2, 1L<<0,key_hook , &vars);
	mlx_loop_hook(vars.mlx, rey, &vars);
	//printf("123123123\n");
	mlx_loop(vars.mlx);
}