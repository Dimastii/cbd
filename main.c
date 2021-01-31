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
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,5,0,0,5,5,0,5,5,0,0,0,7,0,7,0,1},
				{1,0,0,0,0,0,0,5,0,0,0,5,0,0,0,5,0,0,0,0,0,7,0,1},
				{1,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,1},
				{1,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,1},
				{1,0,0,0,0,0,0,5,5,0,0,0,5,0,5,0,0,0,7,7,0,7,0,1},
				{1,6,0,6,0,0,0,6,6,0,0,0,6,0,6,6,0,0,6,6,0,6,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,6,0,0,0,6,6,0,0,0,6,0,6,6,0,0,6,6,0,6,0,1},
				{1,0,0,4,0,0,0,4,4,0,0,0,6,0,2,2,0,0,2,2,0,3,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,2,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,2,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,2,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,5,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,2,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,2,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,2,0,0,0,1},
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
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

typedef struct  s_sprite {
	int offset_mode_cord_sprite_x;
	int offset_mode_cord_sprite_y;

	double enter_on_leny_x;
	double enter_on_leny_y;
	double enter_on_lenx_x;
	double enter_on_lenx_y;
	double len_sprt;

	double len_pred_rey;
	double x_pred;
	double y_pred;

	int create;
}               t_sprite;

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

	t_sprite sprite[100];

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

void ft_round(double min_angle,double *cx, double *cy,t_vars *vars)
{
	if (cos(min_angle) > 0 && sin(min_angle) > 0)
	{
		*cy = (*cy - floor(*cy) > 0) ? floor(*cy) : *cy - 1;
		*cx = (*cx - ceil(*cx) < 0) ? ceil(*cx) : *cx + 1;
		vars->sprite->offset_mode_cord_sprite_x = 1;
		vars->sprite->offset_mode_cord_sprite_y = 1;
	}
	else if (cos(min_angle) < 0 && sin(min_angle) > 0)
	{
		*cy = (*cy - floor(*cy) > 0) ? floor(*cy) : *cy - 1;
		*cx = (*cx - floor(*cx) > 0) ? floor(*cx) : *cx  -1;
		vars->sprite->offset_mode_cord_sprite_x = 1;
		vars->sprite->offset_mode_cord_sprite_y = 0;
	}
	else if (cos(min_angle) < 0 && sin(min_angle) < 0)
	{
		*cy = (*cy - ceil(*cy) < 0) ? ceil(*cy) :*cy + 1;
		*cx = (*cx - floor(*cx) > 0) ? floor(*cx) : *cx - 1;
		vars->sprite->offset_mode_cord_sprite_x = 0;
		vars->sprite->offset_mode_cord_sprite_y = 0;
	}
	else if (cos(min_angle) > 0 && sin(min_angle) < 0)
	{
		*cy = (*cy - ceil(*cy) < 0) ? ceil(*cy) : *cy + 1;
		*cx = (*cx - ceil(*cx) < 0) ? ceil(*cx) : *cx + 1;
		vars->sprite->offset_mode_cord_sprite_x = 0;
		vars->sprite->offset_mode_cord_sprite_y = 1;
	}
	else
		printf("11111111111\n");

}

void	ft_render(t_vars *vars, double len_r, double min_angle, int num)
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

void	ft_render_sprite(double len_to_sprt, double lenx, double x, double y, t_vars *vars)
{
	double xs;
	double ys;
	int i;
	double len_sp;

	len_sp = (sqrt(2) - 1) / 2;
	i = 0;


	while (vars->sprite[i].create != -1)
	{
		xs = fabs((vars->sprite[i].enter_on_lenx_x - vars->sprite->enter_on_lenx_y ) / 2);
		ys = fabs((vars->sprite->enter_on_leny_x - vars->sprite->enter_on_leny_y ) / 2);
		vars->sprite[i].len_sprt -= sqrt(pow(xs - vars->sprite[i].x_pred, 2) + pow(ys - vars->sprite[i].y_pred, 2));

		if ((int)(xs + len_sp * pow(-1,vars->sprite[i].offset_mode_cord_sprite_x)) == (int)xs
		&& (int)(ys + len_sp * pow(-1,vars->sprite[i].offset_mode_cord_sprite_x)) == (int)ys
		&& vars->sprite[i].len_sprt >= 0 )
		{

		}
		i++;
	}
//
//	xs = x + (len_to_sprt - lenx) * pow(-1,vars->sprite[i].offset_mode_cord_sprite_x);
//	ys = y + (len_to_sprt - lenx) * pow(-1,vars->sprite[i].offset_mode_cord_sprite_y);

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

	double x_sprt;
	double y_sprt;
	int	n_sprt;

	double lenx;
	double leny;
	double len;
	double y;
	double x;



	vars->no_so = -1;
	vars->we_ea = -1;


	while (min_angle <= max_angle)
	{
		int i = 0;
		while (i++ < 100)
		{
			vars->sprite[i].create = -1;
		}
		vars->no_so = (sin(min_angle) > 0) ?  1 : 0;
		vars->we_ea = (cos(min_angle) < 0) ?  1 : 0;
		cx = vars->x;
		cy = vars->y;

		lenx = 10000000000;
		leny = 10000000000;

		n_sprt = 0;
		while (cx < mapWidth  && cx > 0)
		{
			ft_round(min_angle, &cx, &cyx, vars);
			len = fabs((vars->x - cx) / (cos(min_angle) + 0.0000002));
			y = vars->y + (len * (sin(min_angle) * -1)) ;
			if (y < mapWidth && y > 0 && worldMap[(int)cx - vars->we_ea][(int)y] == 9)
			{
				vars->sprite[n_sprt].enter_on_lenx_x = cx;
				vars->sprite[n_sprt].enter_on_lenx_y = y;
				vars->sprite[n_sprt].create = 1;
				n_sprt++;
				printf("1\n");

			}
			if (y < mapWidth && y > 0 && worldMap[(int)cx - vars->we_ea][(int)y] != 0)
			{
				lenx = len;
				break;
			}
		}
		n_sprt = 0;
		while (cy < mapHeight && cy > 0)
		{
			ft_round(min_angle, &cyx, &cy, vars);
			len = fabs((vars->y - cy) / (sin(min_angle) + 0.000002));
			x = vars->x + (len * cos(min_angle));
			if (x < mapWidth && x > 0 && worldMap[(int)x][(int)cy - vars->no_so]== 9)
			{
				vars->sprite[n_sprt].enter_on_leny_x = x;
				vars->sprite[n_sprt].enter_on_leny_y = cy;
				vars->sprite[n_sprt].create = 1;
				n_sprt++;
				printf("2\n");

			}
			if (x < mapWidth && x > 0 && (worldMap[(int)x][(int)cy - vars->no_so] != 0))
			{
				leny = len;
				break;
			}
		}


		if (lenx < leny)
		{
			vars->color = (vars->we_ea) ? 0x009932CC : 0x0066CDAA;
			len = lenx;
			vars->we_ea = -1;
		}
		else
		{
			vars->color = (vars->no_so) ? 0x009400D3 : 0x002E8B57;
			len = leny;
			vars->no_so = -1;
		}


		ft_render(vars, len, min_angle, num_rey);
		ft_render_sprite((lenx + leny) / 2 , lenx, cx, y, vars);

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
	int i = 0;
	while (i++ < 100)
	{
		vars.sprite[i].create = -1;
	}


	vars.mlx = mlx_init();

	vars.win = mlx_new_window(vars.mlx, vars.size_win_w, vars.size_win_h, "Gucci flip flops");
	vars.img.img = mlx_new_image(vars.mlx, vars.size_win_w, vars.size_win_h);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);

	mlx_hook(vars.win, 2, 1L<<2,key_hook , &vars);

	mlx_loop_hook(vars.mlx, rey, &vars);

	mlx_loop(vars.mlx);
}