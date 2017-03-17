#ifndef FDF_H
#define FDF_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include <mlx.h>
# include <math.h>



# define WIN_WIDTH		1280
# define WIN_HEIGHT		720

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
	int 			**A;
	int				coord_z;
	int				coord_y;
	int				y;
	int				y1;
	int				z;
	int				z1;
	int				ys;
	int 			xs;
	int				zoom;
	int				iso;
	double		x_val;
	double		angle_y;
	double		angle_z;
	char			*str;
	char			*tempchr;
}					t_coords;

typedef struct		s_colors
{
	int				red;
	int				blue;
	int				green;
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
	t_mlx				mlx;
	t_coords		coords;
	t_colors		colors;
	t_map				map;
}					t_fdf;

void		coordinates(int fd, t_fdf *f, char* argv);
int			fdf_map(t_fdf *f);

#endif
