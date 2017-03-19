/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 03:32:37 by asolis            #+#    #+#             */
/*   Updated: 2017/03/19 03:41:30 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include <mlx.h>
# include <math.h>

# define WIN_WIDTH	1280
# define WIN_HEIGHT	720

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
}					t_mlx;

typedef struct		s_coords
{
	int				tmp;
	int				i;
	int				j;
	int				k;
	int				fd;
	int				ret;
	int				**a;
	int				coord_z;
	int				coord_y;
	int				y;
	int				y1;
	int				z;
	int				z1;
	int				ys;
	int				xs;
	int				zoom;
	int				iso;
	double			x_val;
	double			angle_y;
	double			angle_z;
	char			*str;
	char			*tempchr;
}					t_coords;

typedef struct		s_colors
{
	int				red;
	int				blue;
	int				green;
	int				red_t;
	int				blue_t;
	int				green_t;
}					t_colors;

typedef struct		s_map
{
	char			*data;
	int				bp;
	int				sl;
	int				end;
}					t_map;

typedef struct		s_fdf
{
	t_mlx			mlx;
	t_coords		coords;
	t_colors		colors;
	t_map			map;
}					t_fdf;

void				random_color(t_fdf *f);
void				delete_color(t_fdf *f);
void				coordinates(int fd, t_fdf *f, char *argv);
void				drawing_instructions();
void				drawing_instructions2();
int					fdf_map(t_fdf *f);

#endif
