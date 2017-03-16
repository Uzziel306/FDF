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

int my_key_funct(int keycode)
{
	if (keycode == 53)
		exit(0);

	return (0);
}

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
		coordinates(f->coords.fd, f);
		f->mlx.mlx = mlx_init();
		f->mlx.win = mlx_new_window(f->mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "FDF");
		drawing_base(f->coords.xs, f->coords.ys, f->mlx.mlx, f->mlx.win);
		mlx_key_hook(f->mlx.win, my_key_funct, 0);
		mlx_loop(f->mlx.mlx);
	}
	else
		write(1,"error: you are not passing 1 argument\n",38);
	return (0);
}
