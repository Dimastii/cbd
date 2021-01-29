#include <stdio.h>
#include <math.h>
#include "mlx.h"
#include "fcntl.h"
#include "gnl/get_next_line.h"

//#define PI 3.14159265359
#define ANLGLE M_PI / 2.0
#define N_REY vars->size_win_w


#define mapWidth 5
#define mapHeight 5

int worldMap[mapWidth][mapHeight]=
//		{
//				{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
//				{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
//				{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
//				{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
//				{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
//				{4,0,0,0,0,0,0,5,5,0,5,5,5,5,5,5,0,7,0,7,7,7,7,7},
//				{4,0,0,0,0,0,0,5,0,0,0,5,0,5,0,5,0,0,0,0,7,7,7,1},
//				{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,8},
//				{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
//				{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,8},
//				{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,0,0,7,7,7,1},
//				{4,0,0,0,0,0,0,5,5,0,5,0,5,5,5,5,0,7,7,7,7,7,7,1},
//				{6,6,0,6,0,6,0,6,6,0,6,0,6,6,6,6,0,6,6,6,6,6,6,6},
//				{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
//				{6,6,0,6,0,6,0,6,6,0,6,0,6,6,6,6,0,6,6,6,6,6,6,6},
//				{4,4,0,4,0,4,0,4,4,0,6,0,6,2,2,2,0,2,2,2,3,3,3,3},
//				{4,0,0,0,0,0,0,0,0,0,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
//				{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,0,0,0,2,0,0,0,2},
//				{4,0,0,0,0,0,0,0,0,0,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
//				{4,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,2},
//				{4,0,0,5,0,0,0,0,0,0,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
//				{4,0,0,0,0,0,0,0,0,0,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
//				{4,0,0,0,0,0,0,0,0,0,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
//				{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
//		};
		{
				{4,4,7,7,7},
				{4,0,0,0,7},
				{4,0,1,0,7},
				{4,0,0,0,7},
				{4,1,1,1,7},
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

	double angle_p;

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

	step = 0.1;
	turn = 0.1;
	printf("k_code:! %d\n", keycode);
	mlx_destroy_image(vars->mlx, vars->img.img);
	vars->img.img = mlx_new_image(vars->mlx, vars->size_win_w, vars->size_win_h);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel, &vars->img.line_length, &vars->img.endian);
	if (keycode == 123) {

		if (worldMap[(int) (vars->x - step)][(int) (vars->y)] == 0)
			vars->x -= step;
	}
	if (keycode == 124) {
		if (worldMap[(int) (vars->x + step)][(int) (vars->y)] == 0)
			vars->x += step;
	}
	if (keycode == 125) {
		if (worldMap[(int) (vars->x)][(int) (vars->y + step)] == 0)
			vars->y += step;
	}
	if (keycode == 126) {
		if (worldMap[(int) (vars->x)][(int) (vars->y - step)] == 0)
			vars->y -= step;
	}
	if (keycode == 12) {
		vars->angle_p += turn;
	}
	if (keycode == 14) {
		vars->angle_p -= turn;
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

	int no_so = -1;

	int we_ea = -1;


	double wall_y = vars->size_win_h / 2;

	int sc = 50;
	int n = 1;


	while (min_angle <= max_angle)
	{
		no_so = (sin(min_angle) > 0) ?  1 : 0;
		we_ea = (cos(min_angle) < 0) ?  1 : 0;
		cx = vars->x;
		cy = vars->y;
		//printf("------%d----- %f |sin = %f |cos = %f \n",num_rey , min_angle ,sin(min_angle) ,cos(min_angle));

		lenx = 10000000000;
		leny = 10000000000;

		//write_map(vars);
		wall_y = 0;
		while (cx < mapWidth  && cx > 0)
		{


			ft_round(min_angle, &cx, &cyx);
			len = fabs((vars->x - cx) / (cos(min_angle) + 0.0000002));
			y = vars->y + (len * (sin(min_angle) * -1)) ;

			//printf("cx = %f y = %f | len = %f <-->" , cx, y, len);
			if (y < mapWidth && y > 0 && worldMap[(int)cx - we_ea][(int)y] != 0)
			{
				lenx = fabs((vars->x - cx) / (cos(min_angle) + 0.0000002));
				break;
			}
			n++;
		}
		n = 1;
		//printf("\n");
		while (cy < mapHeight && cy > 0)
		{
			ft_round(min_angle, &cyx, &cy);
			len = fabs((vars->y - cy) / (sin(min_angle) + 0.000002));
			x = vars->x + (len * cos(min_angle));
			//printf("x = %f cy = %f | len = %f <-->" ,x, cy, len);
			if (x < mapWidth && x > 0 && (worldMap[(int)x][(int)cy - no_so] != 0))
			{

				leny = fabs((vars->y - cy) / (sin(min_angle) + 0.000002));
				break;
			}
			n++;
		}

	//	printf("\n");
		if (fabs(lenx) < fabs(leny))
		{
			len = fabs(lenx);
			we_ea = -1;
		//	printf("len %f | \n", len);
			my_mlx_pixel_put(&vars->img,cx * 10 , y  * 10 , 0x00FF0000);
		}
		else
		{
			len = fabs(leny);
			no_so = -1;
		//	printf("len %f | \n", len);
			my_mlx_pixel_put(&vars->img, x  * 10, cy  * 10 , 0x00FF0000);

		}
		num_rey++;
		min_angle += angle_offset;
		my_mlx_pixel_put(&vars->img,vars->x * 10 , vars->y  * 10 , 0x00FF0000);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}

int             main(void)
{
	t_vars      vars;

	vars.size_win_w = 100;
	vars.size_win_h = 100;

	vars.x = 1.5;
	vars.y = 1.5;
	vars.key = -1;
	vars.angle_p = M_PI;

	vars.mlx = mlx_init();

	vars.win = mlx_new_window(vars.mlx, vars.size_win_w, vars.size_win_h, "Gucci flip flops");
	vars.img.img = mlx_new_image(vars.mlx, vars.size_win_w, vars.size_win_h);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);

	mlx_hook(vars.win, 2, 1L<<0,key_hook , &vars);

	mlx_loop_hook(vars.mlx, rey, &vars);

	mlx_loop(vars.mlx);
}