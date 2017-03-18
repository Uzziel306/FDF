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
	f->coords.iso = 20;
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

int	my_key_(int keycode, t_fdf *f)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 12)
		f->coords.x_val += 1;
	else if (keycode == 14)
		f->coords.x_val -= 1;
	return (0);
}

static int my_key_funct(int keycode, t_fdf *f)
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
			printf("%d\n",keycode );
	return (0);
}
// w = 13, a = 0, s = 1, d = 2, 126, 123, 125, 124
void	drawing_instructions()
{
	ft_putstr("|----|FDF --------- MENU|-----|\n");
	ft_putstr("|-----------------------------|\n");
	ft_putstr("|Use the arrows of your       |\n");
	ft_putstr("|keyborad to move the map.    |\n");
	ft_putstr("| [^] [<] [>] [down]          |\n");
	ft_putstr("|-----------------------------|\n");
	ft_putstr("|Press 'R' to remake the map. |\n");
	ft_putstr("|NOTE: The map it's gona have |\n");
	ft_putstr("|same color and the same posi |\n");
	ft_putstr("|tion that had in the beginnig|\n");
	ft_putstr("|-----------------------------|\n");
	ft_putstr("|Press 'C' to randoom colors. |\n");
	ft_putstr("|-----------------------------|\n");
	ft_putstr("|Press 'W' to rotate the map. |\n");
	ft_putstr("|-----------------------------|\n");
	ft_putstr("|Press 'S' to rotate the map. |\n");
	ft_putstr("|-----------------------------|\n");
	ft_putstr("|Press 'A' to expand the map. |\n");
	ft_putstr("|-----------------------------|\n");
	ft_putstr("|Press 'D' to contract the map|\n");
	ft_putstr("|-----------------------------|\n");
	ft_putstr("|Press 'Z' to zoom in the map |\n");
	ft_putstr("|-----------------------------|\n");
	ft_putstr("|Press 'X' to zoom out the map|\n");
	ft_putstr("|-----------------------------|\n");
	ft_putstr("|Press 'ESC to exit and close |\n");
	ft_putstr("|the window.                  |\n");
	ft_putstr("|-----------------------------|\n");
}

int		main(int argc, char *argv[])
{
	t_fdf *f;

	f = (t_fdf*)malloc(sizeof(t_fdf));
	if (argc == 2)
	{
		drawing_instructions();
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
		write(1,"error: you are not passing 1 argument\n",38);
	return (0);
}
