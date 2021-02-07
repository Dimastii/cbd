
#include <stdio.h>
#include <math.h>
#include "mlx.h"
#include "fcntl.h"
#include "gnl/get_next_line.h"

#define ANLGLe M_PI / 4
#define N_REY vars->size_win_w


#define mapWidth  24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
		{
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,9,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,1,0,0,0,0,0,0,0,9,1,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,1,9,1,0,0,0,0,0,0,1,9,1,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,9,0,0,0,9,1,9,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,9,1,9,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,9,1,9,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,9,9,0,0,9,1,9,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,9,1,9,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,9,0,0,0,9,1,9,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,9,1,9,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,9,0,9,1,9,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,9,1,9,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,9,1,9,1},
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};
//		{
//				{1,1,1,1,1},
//				{1,0,0,0,1},
//				{1,0,9,0,1},
//				{1,0,0,0,1},
//				{1,1,1,1,1},
//		};



typedef struct  s_image {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
	int 		w;
	int 		h;
}               t_image;

typedef struct  s_sprite_cord {

	float enter_on_len_x;
	float enter_on_leny_y;
	float enter_on_lenx_x;
	float enter_on_lenx_y;
	float len_to_sprt;


}               t_sprite_cord;

typedef struct  s_sprite {
	int offset_mode_cord_sprite_x;
	int offset_mode_cord_sprite_y;

	t_sprite_cord cord;

	float enter_on_len_x;
	float enter_on_len_y;


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

	t_image 		img;
	t_image		img_tex;
	t_image		img_tex_sp;
	double x_tex;
	double y_tex;

	int key_del;
}               t_vars;


void rey(t_vars* vars);
int ft_len_sprt(t_vars *vars, double ang, float len);


void            my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int            my_mlx_pixel_take(t_image data, int x, int y)
{
	char    *dst;
	int color;

	dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
	color = *(unsigned int*)dst;
	return (color);
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
//		if (worldMap[(int) (vars->x - 0.5)][(int) (vars->y - 0.5)] != 1) {
		vars->x -= step * sin(vars->angle_p);
		vars->y -= step * cos(vars->angle_p);
//		}
	}
	if (keycode == 123) {
//		if (worldMap[(int) (vars->x + 0.5)][(int) (vars->y + 0.5)] != 1) {

		vars->x += step * sin(vars->angle_p);
		vars->y += step * cos(vars->angle_p);
//		}
	}
	if (keycode == 125) {
//		if (worldMap[(int)(vars->x - 0.5)][(int)(vars->y +0.5)] != 1) {
		vars->x -= step * cos(vars->angle_p);
		vars->y += step * sin(vars->angle_p);
//		}
	}
	if (keycode == 126) {
//		if (worldMap[(int) (vars->x + 0.5)][(int) (vars->y - 0.5)] != 1) {
		vars->x += step * cos(vars->angle_p);
		vars->y -= step * sin(vars->angle_p);
//		}
	}
	if (keycode == 12) {
		vars->angle_p -= turn;
	}
	if (keycode == 14) {
		vars->angle_p += turn;
	}
}

void ft_round(double min_angle,double *cx, double *cy,t_vars *vars)
{
	if (cos(min_angle) > 0 && sin(min_angle) > 0)
	{
		*cx = (*cx - ceil(*cx) < 0) ? ceil(*cx) : *cx + 1;
		*cy = (*cy - floor(*cy) > 0) ? floor(*cy) : *cy - 1;
		vars->sprite->offset_mode_cord_sprite_x = 0;
		vars->sprite->offset_mode_cord_sprite_y = 1;
	}
	else if (cos(min_angle) < 0 && sin(min_angle) > 0)
	{
		*cx = (*cx - floor(*cx) > 0) ? floor(*cx) : *cx  -1;
		*cy = (*cy - floor(*cy) > 0) ? floor(*cy) : *cy - 1;
		vars->sprite->offset_mode_cord_sprite_x = 0;
		vars->sprite->offset_mode_cord_sprite_y = 1;
	}
	else if (cos(min_angle) < 0 && sin(min_angle) < 0)
	{
		*cx = (*cx - floor(*cx) > 0) ? floor(*cx) : *cx - 1;
		*cy = (*cy - ceil(*cy) < 0) ? ceil(*cy) :*cy + 1;
		vars->sprite->offset_mode_cord_sprite_x = 0;
		vars->sprite->offset_mode_cord_sprite_y = 1;
	}
	else if (cos(min_angle) > 0 && sin(min_angle) < 0)
	{
		*cx = (*cx - ceil(*cx) < 0) ? ceil(*cx) : *cx + 1;
		*cy = (*cy - ceil(*cy) < 0) ? ceil(*cy) : *cy + 1;
		vars->sprite->offset_mode_cord_sprite_x = 0;
		vars->sprite->offset_mode_cord_sprite_y = 1;
	}
}

void	ft_render(t_vars *vars, double len_r_norm, double min_angle, int num)
{
	int wall_y;

	double wall_h = vars->size_win_h / len_r_norm;
	int drawStart = -wall_h / 2 + vars->size_win_h / 2;
	int drawend = wall_h / 2 + vars->size_win_h / 2;
//	if (drawStart <0) drawStart = 0;
//	if (drawend >= vars->size_win_h) drawend = vars->size_win_h - 1;


	int wall_y1 = drawStart;
	int color;
	wall_y = 0;
	int y = 0;
	while (wall_y1 < drawend)
	{
		y = (int)(((float)(wall_y1 - drawStart) /((float)drawend - (float)drawStart)) * 700.0);
		color = my_mlx_pixel_take(vars->img_tex,(int)((vars->x_tex - (int)vars->x_tex) * 700.0), y);
		if (wall_y1 >= 0 && wall_y1 < vars->size_win_h)
			my_mlx_pixel_put(&vars->img, num - 1 ,wall_y1, color);

		wall_y1++;
		wall_y++;
	}
}
unsigned int yyy = 0xDC143C;
void	ft_print_wall_sprite(t_vars *vars, double len_r, int num_rey)
{
	double wall_h = vars->size_win_h / (len_r);
	int drawStart = -wall_h / 2 + vars->size_win_h / 2;
	int drawend = wall_h / 2 + vars->size_win_h / 2;
	if (drawStart <0) drawStart = 0;
	if (drawend >= vars->size_win_h) drawend = vars->size_win_h - 1;
	int color;

	wall_h = drawStart;

	while (wall_h < drawend)
	{
		color = my_mlx_pixel_take(vars->img_tex_sp, (num_rey - 1) % 64, wall_h);
		my_mlx_pixel_put(&vars->img, num_rey - 1 ,wall_h, color);
		wall_h++;
	}
}

void	ft_render_sprite(t_vars *vars , int num_rey, double min_angle)
{
	int i;

	i = 0;
	while (vars->sprite[i].create != -1) {
		i++;
	}

	while (i--)
	{
		if (ft_len_sprt(vars, min_angle, vars->sprite[i].cord.len_to_sprt))
		ft_print_wall_sprite(vars,vars->sprite[i].cord.len_to_sprt, num_rey);

	}
}

void ft_round_sprt_x(double angl, float *x, float *y)
{
	if (cos(angl) < 0)
	{
		*y = ceilf(*y) - (float)0.5;
		*x -= (float)0.5;
	}
	else if (cos(angl) > 0)
	{
		*y = ceilf(*y) - (float)0.5;
		*x += (float)0.5;
	}
}

void ft_round_sprt_y(double angl, float *x, float *y)
{
	if (sin(angl) < 0)
	{
		*x = ceilf(*x) - (float)0.5;
		*y += (float)0.5;
	}
	else if (sin(angl) > 0)
	{
		*x = ceilf(*x) - (float)0.5;
		*y -= (float)0.5;
	}
}
void ft_sort_sprt(t_vars *vars )
{
	int i = 0;
	int j;
	float temp;
	while (vars->sprite[i].create != -1)
	{
		j = i + 1;
		while (vars->sprite[j].create != -1)
		{
			if (vars->sprite[j].cord.len_to_sprt < vars->sprite[i].cord.len_to_sprt)
			{
				temp = vars->sprite[j].cord.len_to_sprt;
				vars->sprite[j].cord.len_to_sprt = vars->sprite[i].cord.len_to_sprt;
				vars->sprite[i].cord.len_to_sprt = temp;
			}
			j++;
		}
		i++;
	}

}

int ft_len_sprt(t_vars *vars, double ang, float len)
{
	double a1;
	double a2;

	a1 = vars->angle_p - asin(0.5 / sqrt(pow(len, 2) + 0.25));
	a2 = vars->angle_p + asin(0.5 / sqrt(pow(len, 2) + 0.25));
	if (ang < a1 || ang > a2)
		return (0);
	else
		return (1);
}
void rey(t_vars* vars)
{
	double cx;
	double cy;
	double cyx;


	double angle_offset = ANLGLe / N_REY;
	double max_angle = vars->angle_p + ANLGLe / 2.0;
	double min_angle = vars->angle_p - ANLGLe / 2.0;

	int num_rey = 1;

	int	n_sprt;
	int	gran = 0;

	double lenx;
	double leny;
	double len;
	double y;
	double x;


	int i;
	gran = 0;
	while (min_angle <= max_angle)
	{
		i = -1;
		while (i++ < 100)
		{
			vars->sprite[i].create = -1;
			vars->sprite[i].len_sprt = 1;
			vars->sprite[i].cord.len_to_sprt = -1;
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
			len = fabs((vars->x - cx) / (cos(min_angle) - 0.0000002));
			y = vars->y + (len * (sin(min_angle) * -1));
			if (y < mapWidth && y > 0 && worldMap[(int)cx - vars->we_ea][(int)y] == 1)
			{
				lenx = len;
				break;

			}
			if (y < mapWidth && y > 0 && worldMap[(int)cx - vars->we_ea][(int)y] == 9 )
			{
				vars->sprite->enter_on_len_x = (float)cx;
				vars->sprite->enter_on_len_y = (float)y;

				ft_round_sprt_x(min_angle,&vars->sprite->enter_on_len_x, &vars->sprite->enter_on_len_y);
				if (vars->sprite[n_sprt].cord.len_to_sprt == -1)
				vars->sprite[n_sprt].cord.len_to_sprt = sqrtf(powf(vars->sprite->enter_on_len_x - (float)vars->x, 2) + powf(vars->sprite->enter_on_len_y - (float)vars->y, 2));
				vars->sprite[n_sprt].create = 1;
				n_sprt++;
			}
		}

		while (cy < mapHeight && cy > 0)
		{
			ft_round(min_angle, &cyx, &cy, vars);
			len = fabs((vars->y - cy) / (sin(min_angle) - 0.000002));
			x = vars->x - (len * cos(min_angle)  * - 1);
			if (x < mapWidth && x > 0 && (worldMap[(int)x][(int)cy - vars->no_so] == 1))
			{
				leny = len;
				break;
			}
			if (x < mapWidth && x > 0 && worldMap[(int)x][(int)cy - vars->no_so] == 9)
			{
				vars->sprite->enter_on_len_x = (float)x;
				vars->sprite->enter_on_len_y= (float)cy;

				ft_round_sprt_y(min_angle,&vars->sprite->enter_on_len_x, &vars->sprite->enter_on_len_y);
				if (vars->sprite[n_sprt].cord.len_to_sprt == -1)
					vars->sprite[n_sprt].cord.len_to_sprt = sqrtf(powf(vars->sprite->enter_on_len_x - (float)vars->x, 2) + powf(vars->sprite->enter_on_len_y - (float)vars->y, 2));
				vars->sprite[n_sprt].create = 1;
				n_sprt++;
			}
		}


		if (lenx < leny)
		{
			vars->color = (vars->we_ea) ? 0x009932CC : 0x0066CDAA;
			len = lenx * fabs(sin(vars->angle_p + M_PI/2 - min_angle));
			vars->we_ea = -1;
			vars->x_tex = cx;
			vars->x_tex = y;
			yyy = 0xDC143C;
		}
		else
		{
			vars->color = (vars->no_so) ? 0x009400D3 : 0x002e8B57;
			len = leny * fabs(sin(vars->angle_p + M_PI/2 - min_angle));
			vars->no_so = -1;
			vars->x_tex = x;
			vars->y_tex = cy;
			yyy = 0xDCFF3C;
		}
		ft_render(vars, len, min_angle, num_rey);

		printf("%d | %d) %f || %f \n",num_rey,0,vars->sprite[0].cord.len_to_sprt, len);
		printf("%d | %d) %f || %f \n",num_rey,1,vars->sprite[1].cord.len_to_sprt, len);

		ft_sort_sprt(vars);
		if (len > vars->sprite[0].cord.len_to_sprt ) {
			ft_render_sprite(vars, num_rey, min_angle);
		}

		num_rey++;
		min_angle += angle_offset;
	}

	vars->key_del = -1;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}

int             main(void)
{
	t_vars      vars;
	int i = 0;


	vars.size_win_w = 1000;
	vars.size_win_h = 1000;

	vars.x =4;
	vars.y =5;
	vars.angle_p =- M_PI /2;
	while (i++ < 100)
	{
		vars.sprite[i].create = -1;
	}

	vars.mlx = mlx_init();


	vars.win = mlx_new_window(vars.mlx, vars.size_win_w, vars.size_win_h, "Gucci flip flops");
	vars.img.img = mlx_new_image(vars.mlx, vars.size_win_w, vars.size_win_h);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);

	vars.img_tex_sp.img = mlx_xpm_file_to_image(vars.mlx, "./sp_anime.xpm", &vars.img_tex_sp.w, &vars.img_tex_sp.h);
	vars.img_tex_sp.addr = mlx_get_data_addr(vars.img_tex_sp.img, &vars.img_tex_sp.bits_per_pixel, &vars.img_tex_sp.line_length, &vars.img_tex_sp.endian);


	vars.img_tex.img = mlx_xpm_file_to_image(vars.mlx, "./anime.xpm", &vars.img_tex.w, &vars.img_tex.h);
	vars.img_tex.addr = mlx_get_data_addr(vars.img_tex.img, &vars.img_tex.bits_per_pixel, &vars.img_tex.line_length, &vars.img_tex.endian);

	mlx_hook(vars.win, 2, 1L<<2,key_hook , &vars);
	mlx_loop_hook(vars.mlx, rey, &vars);
	mlx_loop(vars.mlx);
}