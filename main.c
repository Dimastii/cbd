

#include "cub.h"
unsigned int yyy = 0xDC143C;

int worldMap[mapWidth][mapHeight]=
		{//      1 2 3 4 5 6 7 8 9 10111213141516171819
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,1,9,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};
//		{
//				{1,1,1,1,1},
//				{1,0,0,0,1},
//				{1,0,9,0,1},
//				{1,0,0,0,1},
//				{1,1,1,1,1},
//		};





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

	step = 0.27;
	turn = 0.05;
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

void	ft_render_wall(t_vars *vars, double len_r_norm, int num)
{
	int wall_y;
	double wall_h = vars->size_win_h / len_r_norm;
	int drawStart = -wall_h / 2 + vars->size_win_h / 2;
	int drawend = wall_h / 2 + vars->size_win_h / 2;
	int wall_y1 = drawStart;
	int color;
	int y;

	wall_y = 0;
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


int ft_len_sprt(t_vars *vars, double ang, t_sprite *sprt)
{
	double a1;
	double a2;
	double angle_sptr;
	float h_x;
	double ang_range;

	ang_range = atan(0.5 / sprt->cord.len_to_sprt);

	h_x = sprt->enter_on_len_x - (float)vars->x;
	angle_sptr = atan(fabs((sprt->enter_on_len_y - vars->y))/fabs((sprt->enter_on_len_x - vars->x)));
	if (ang <= angle_sptr + 0.05 && ang >= angle_sptr - 0.05) {
		printf("Sprt =%f    ang=%f\n", angle_sptr, ang);
		vars->color = 0xDCFF3C;
	}
	else
		vars->color = 0xDCFFFF;

	a1 = angle_sptr - ang_range;
	a2 = angle_sptr + ang_range;


	if (sin(ang) >= sin(a1) && sin(ang) <= sin(a2))
		return (1);
	else
		return (1);
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

	int	n_sprt;

	double lenx;
	double leny;
	double len;
	double y;
	double x;


	int i;
	while (min_angle <= max_angle)
	{
		i = -1;
		while (i++ < 100)
		{
			vars->sprite[i].create = -1;
			vars->sprite[i].cord.len_to_sprt = -1;
			vars->sprite[i].cord.num = 0;
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
			//vars->color = (vars->we_ea) ? 0x009932CC : 0x0066CDAA;
			len = lenx * fabs(sin(vars->angle_p + M_PI/2 - min_angle));
			vars->we_ea = -1;
			vars->x_tex = cx;
			vars->x_tex = y;
			yyy = 0xDC143C;
		}
		else
		{
		//	vars->color = (vars->no_so) ? 0x009400D3 : 0x002e8B57;
			len = leny * fabs(sin(vars->angle_p + M_PI/2 - min_angle));
			vars->no_so = -1;
			vars->x_tex = x;
			vars->y_tex = cy;
			yyy = 0xDCFF3C;
		}
		ft_render_wall(vars, len, num_rey);

		ft_sort_sprt(vars);
//		if (len > vars->sprite[0].cord.len_to_sprt ) {
			if (vars->sprite[0].cord.len_to_sprt != -1)
				ft_render_sprite(vars, num_rey, min_angle);

//		}
		num_rey++;
		min_angle += angle_offset;
	}

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
	vars.angle_p =0;
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