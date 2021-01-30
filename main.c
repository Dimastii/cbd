#include <stdio.h>
#include <math.h>
#include "mlx.h"
#include "fcntl.h"
#include "gnl/get_next_line.h"

//#define PI 3.14159265359
#define ANLGLE M_PI / 5
#define N_REY vars->size_win_w


#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
		{
				{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
				{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
				{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
				{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
				{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
				{4,0,0,0,0,0,0,5,5,0,0,5,5,0,5,5,0,0,0,7,0,7,0,7},
				{4,0,0,0,0,0,0,5,0,0,0,5,0,0,0,5,0,0,0,0,0,7,0,1},
				{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,8},
				{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,1},
				{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,8},
				{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,0,0,0,7,0,1},
				{4,0,0,0,0,0,0,5,5,0,0,0,5,0,5,5,0,0,7,7,0,7,0,1},
				{6,6,0,6,0,0,0,6,6,0,0,0,6,0,6,6,0,0,6,6,0,6,0,6},
				{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
				{6,0,0,6,0,0,0,6,6,0,0,0,6,0,6,6,0,0,6,6,0,6,0,6},
				{4,0,0,4,0,0,0,4,4,0,0,0,6,0,2,2,0,0,2,2,0,3,0,3},
				{4,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,2,0,0,0,2},
				{4,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,2,0,0,0,2},
				{4,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,2,0,0,0,2},
				{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
				{4,0,0,5,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,2,0,0,0,2},
				{4,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,2,0,0,0,2},
				{4,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,2,0,0,0,2},
				{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
		};
//		{
//				{4,4,7,7,7},
//				{4,0,0,0,7},
//				{4,0,1,0,7},
//				{4,0,0,0,7},
//				{4,1,1,1,7},
//		};



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

	double angle_p;

	int no_so;
	int we_ea;
	unsigned long color;

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

	step = 0.17;
	turn = 0.09;
	printf("k_code:! %d\n", keycode);
	mlx_destroy_image(vars->mlx, vars->img.img);
	vars->img.img = mlx_new_image(vars->mlx, vars->size_win_w, vars->size_win_h);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	if (keycode == 124) {
		vars->x -= step * sin(vars->angle_p);
		vars->y -= step * cos(vars->angle_p);
	}
	if (keycode == 123) {
		vars->x += step * sin(vars->angle_p);
		vars->y += step * cos(vars->angle_p);
	}
	if (keycode == 125) {
		vars->x -= step * cos(vars->angle_p);
		vars->y += step * sin(vars->angle_p);
	}
	if (keycode == 126) {
		vars->x += step * cos(vars->angle_p);
		vars->y -= step * sin(vars->angle_p);
	}
	if (keycode == 12) {
		vars->angle_p -= turn;
	}
	if (keycode == 14) {
		vars->angle_p += turn;
	}
}

void	write_map(t_vars* vars)
{
	int i = mapWidth;
	int j = mapHeight;
	int sc1 = vars->size_win_w / mapWidth;
	int sc2 = vars->size_win_w / mapHeight;
	while (i--)
	{
		j = mapHeight;
		while (j--) {
			if (worldMap[j][i] == 0) {
				sc1 = vars->size_win_w / mapWidth;
				while (sc1-- != 0) {
					sc2 = vars->size_win_w / mapHeight;
					while (sc2-- != 0)
					my_mlx_pixel_put(&vars->img, (int) (j * (vars->size_win_h / mapHeight) + sc2),
									 (int) (i * (vars->size_win_w / mapWidth) + sc1), 0x8800FF00);
					//my_mlx_pixel_put(&vars->img, (int) (j * (vars->size_win_h / mapHeight) + sc),(int) (i * (vars->size_win_w / mapWidth) + sc), 0x8800FF00);
				}
			}
		}
	}
}

void ft_round(double min_angle,double *cx, double *cy)
{
	if (cos(min_angle) > 0 && sin(min_angle) > 0)
	{
		*cy = (*cy - floor(*cy) > 0) ? floor(*cy) : *cy - 1;
		*cx = (*cx - ceil(*cx) < 0) ? ceil(*cx) : *cx + 1;
	}
	else if (cos(min_angle) < 0 && sin(min_angle) > 0)
	{
		*cy = (*cy - floor(*cy) > 0) ? floor(*cy) : *cy - 1;
		*cx = (*cx - floor(*cx) > 0) ? floor(*cx) : *cx  -1;
	}
	else if (cos(min_angle) < 0 && sin(min_angle) < 0)
	{
		*cy = (*cy - ceil(*cy) < 0) ? ceil(*cy) :*cy + 1;
		*cx = (*cx - floor(*cx) > 0) ? floor(*cx) : *cx - 1;
	}
	else if (cos(min_angle) > 0 && sin(min_angle) < 0)
	{
		*cy = (*cy - ceil(*cy) < 0) ? ceil(*cy) : *cy + 1;
		*cx = (*cx - ceil(*cx) < 0) ? ceil(*cx) : *cx + 1;
	}
	else
		printf("11111111111\n");

}

ft_render(t_vars *vars, double len_r, double min_angle, int num)
{
	int wall_y;

	double real_len = len_r * fabs(sin(vars->angle_p + M_PI/2 - min_angle));
	double wall_h = vars->size_win_h / real_len;
	int drawStart = -wall_h / 2 + vars->size_win_h / 2;
	int drawEnd = wall_h / 2 + vars->size_win_h / 2;
	if (drawStart <0) drawStart = 0;
	if (drawEnd >= vars->size_win_h) drawEnd = vars->size_win_h - 1;


	wall_y = drawStart;

	while (wall_y < drawEnd)
	{
		my_mlx_pixel_put(&vars->img, num - 1 ,wall_y, vars->color);
		wall_y++;
	}
}

void rey(t_vars* vars)
{
	double cx;
	double cy;
	double cyx;


	double angle_offset = ANLGLE / N_REY;
	double max_angle = vars->angle_p + ANLGLE / 2.0;
	double min_angle = vars->angle_p - ANLGLE / 2.0;

	int num_rey = 1;

	double lenx;
	double leny;
	double len;
	double y;
	double x;

	vars->no_so = -1;

	vars->we_ea = -1;

	int n = 1;


	while (min_angle <= max_angle)
	{
		vars->no_so = (sin(min_angle) > 0) ?  1 : 0;
		vars->we_ea = (cos(min_angle) < 0) ?  1 : 0;
		cx = vars->x;
		cy = vars->y;

		lenx = 10000000000;
		leny = 10000000000;

		while (cx < mapWidth  && cx > 0)
		{

			ft_round(min_angle, &cx, &cyx);
			len = fabs((vars->x - cx) / (cos(min_angle) + 0.0000002));
			y = vars->y + (len * (sin(min_angle) * -1)) ;

			if (y < mapWidth && y > 0 && worldMap[(int)cx - vars->we_ea][(int)y] != 0)
			{
				lenx = fabs((vars->x - cx) / (cos(min_angle) + 0.0000002));
				break;
			}
			n++;
		}
		n = 1;
		while (cy < mapHeight && cy > 0)
		{
			ft_round(min_angle, &cyx, &cy);
			len = fabs((vars->y - cy) / (sin(min_angle) + 0.000002));
			x = vars->x + (len * cos(min_angle));
			if (x < mapWidth && x > 0 && (worldMap[(int)x][(int)cy - vars->no_so] != 0))
			{

				leny = fabs((vars->y - cy) / (sin(min_angle) + 0.000002));
				break;
			}
			n++;
		}

		if (fabs(lenx) < fabs(leny))
		{
			vars->color = (vars->we_ea) ? 0x009932CC : 0x0066CDAA;
			len = fabs(lenx);
			vars->we_ea = -1;
//			my_mlx_pixel_put(&vars->img,cx * vars->size_win_h  / mapHeight, y  * vars->size_win_h  / mapHeight , color);
		}
		else
		{
			vars->color = (vars->no_so) ? 0x009400D3 : 0x002E8B57;
			len = fabs(leny);
			vars->no_so = -1;
//			my_mlx_pixel_put(&vars->img, x  * vars->size_win_w / mapWidth, cy  * vars->size_win_h  / mapHeight , color);
		}

		ft_render(vars, len, min_angle, num_rey);

		num_rey++;
		min_angle += angle_offset;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}

int             main(void)
{
	t_vars      vars;

	vars.size_win_w = 1000;
	vars.size_win_h = 1000;

	vars.x = 1.5;
	vars.y = 1.5;
	vars.angle_p = 0;

	vars.mlx = mlx_init();

	vars.win = mlx_new_window(vars.mlx, vars.size_win_w, vars.size_win_h, "Gucci flip flops");
	vars.img.img = mlx_new_image(vars.mlx, vars.size_win_w, vars.size_win_h);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);

	mlx_hook(vars.win, 2, 1L<<2,key_hook , &vars);

	mlx_loop_hook(vars.mlx, rey, &vars);

	mlx_loop(vars.mlx);
}