/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 15:28:49 by asolis            #+#    #+#             */
/*   Updated: 2017/03/19 03:18:19 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	reset_map(t_fdf *f)
{
	f->coords.coord_z = 0;
	f->coords.coord_y = 0;
	f->coords.x_val = 5.50;
	f->coords.angle_y = cos(M_PI / 3);
	f->coords.angle_z = f->coords.angle_y * sin(M_PI / 6);
	f->coords.zoom = (f->coords.xs < 99) ? 100 - f->coords.ys : 8;
	f->coords.iso = 2;
	f->colors.red = f->colors.red_t;
	f->colors.green = f->colors.green_t;
	f->colors.blue = f->colors.blue_t;
}

void		get_color(t_fdf *f, char *red, char *green, char *blue)
{
	f->colors.red_t = ft_atoi(red);
	f->colors.green_t = ft_atoi(green);
	f->colors.blue_t = ft_atoi(blue);
}

int			my_key_(int keycode, t_fdf *f)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 12)
		f->coords.x_val += 1;
	else if (keycode == 14)
		f->coords.x_val -= 1;
	else if (keycode == 9)
		delete_color(f);
	return (0);
}

static int	my_key_funct(int keycode, t_fdf *f)
{
	if (keycode == 8)
		random_color(f);
	else if (keycode == 15)
		reset_map(f);
	else if (keycode == 126)
		f->coords.coord_z += 7;
	else if (keycode == 125)
		f->coords.coord_z -= 7;
	else if (keycode == 123)
		f->coords.coord_y += 7;
	else if (keycode == 124)
		f->coords.coord_y -= 7;
	else if (keycode == 13)
		f->coords.angle_z += 0.1;
	else if (keycode == 1)
		f->coords.angle_z -= 0.1;
	else if (keycode == 0)
		f->coords.angle_y += 0.02;
	else if (keycode == 2)
		f->coords.angle_y -= 0.02;
	else if (keycode == 6)
		f->coords.zoom += 10;
	else if (keycode == 7)
		f->coords.zoom -= 10;
	return (0);
}

int			main(int argc, char *argv[])
{
	t_fdf *f;

	f = (t_fdf*)malloc(sizeof(t_fdf));
	if (argc == 5)
	{
		drawing_instructions();
		drawing_instructions2();
		get_color(f, argv[2], argv[3], argv[4]);
		f->coords.fd = open(argv[1], O_RDONLY);
		coordinates(f->coords.fd, f, argv[1]);
		f->mlx.mlx = mlx_init();
		f->mlx.win = mlx_new_window(f->mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "FDF");
		reset_map(f);
		mlx_key_hook(f->mlx.win, my_key_, f);
		mlx_hook(f->mlx.win, 2, 3, my_key_funct, f);
		mlx_loop_hook(f->mlx.mlx, fdf_map, f);
		mlx_loop(f->mlx.mlx);
	}
	else
	{
		write(1, "error: you are not passing the all arguments\n", 45);
		ft_putstr("READ THE INSTRUCTIONS.\n");
	}
	return (0);
}
