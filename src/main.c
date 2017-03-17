/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 15:28:49 by asolis            #+#    #+#             */
/*   Updated: 2017/03/15 15:28:53 by asolis           ###   ########.fr       */
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
	f->coords.iso = 3;
	f->colors.red = 0x4F;
	f->colors.green = 0x4F;
	f->colors.blue = 0x4F;
}


static void	random_color(t_fdf *f)
{
	f->colors.red = (rand() % 0x7F);
	f->colors.green = (rand() % 0x7F);
	f->colors.blue = (rand() % 0x7F);
}

static int my_key_funct(int keycode, t_fdf *f)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 46)
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
	printf("%d\n",keycode );
	return (0);
}
// w = 13, a = 0, s = 1, d = 2, 126, 123, 125, 124
void	drawing_base(int x, int y, void *mlx, void *win)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(j <= y)
	{
		while(i <= x)
		{
			mlx_pixel_put(mlx, win, i, j, 0x66FFFF);
			i++;
		}
		i = 0;
		j++;
	}
}

int		main(int argc, char *argv[])
{
	t_fdf *f;

	f = (t_fdf*)malloc(sizeof(t_fdf));
	if (argc == 2)
	{
		f->coords.fd = open(argv[1], O_RDONLY);
		coordinates(f->coords.fd, f, argv[1]);
		f->mlx.mlx = mlx_init();
		f->mlx.win = mlx_new_window(f->mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "FDF");
		reset_map(f);
		mlx_hook(f->mlx.win, 2, 3, my_key_funct, f);
		mlx_loop_hook(f->mlx.mlx, fdf_map, f);
		mlx_loop(f->mlx.mlx);
	}
	else
		write(1,"error: you are not passing 1 argument\n",38);
	return (0);
}
