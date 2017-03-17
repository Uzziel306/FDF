#include "fdf.h"

static void	put_pixel(t_fdf *f, int y, int z, double uvector)
{
	int		pos;
	int		sign;

	if ((y > 0 && z > 0) && (y < WIN_WIDTH && z < WIN_HEIGHT))
	{
		pos = (y * 4) + (z * WIN_WIDTH * 4);
		sign = (f->coords.x_val < 0) ? -1 : 1;
		f->map.data[pos] = f->colors.red + uvector;
		f->map.data[pos + 1] = f->colors.green + uvector;
		f->map.data[pos + 2] = f->colors.blue + uvector;
	}
}

// map = coords, image = map
//height = ys. width = xs
// y0 = y, z0 = z
//width = xs , height = ys

static void	draw_lines(t_fdf *f)
{
	double y;
	double z;
	double delta_y;
	double delta_z;
	double uvector;

	y = f->coords.y;
	z = f->coords.z;
	delta_y = f->coords.y1 - f->coords.y;
	delta_z = f->coords.z1 - f->coords.z;
	uvector = sqrt((pow(delta_y, 2)) + (pow(delta_z, 2)));
	delta_y /= uvector;
	delta_z /= uvector;
	while (uvector > 0)
	{
		put_pixel(f, y, z, uvector);
		y += delta_y;
		z += delta_z;
		uvector -= 1;
	}
}


static void	draw_map(t_fdf *f, int y, int z, char c)
{
	int		yt;
	int		zt;

	yt = y - f->coords.xs / 2;
	zt = z - f->coords.ys  / 2;
	f->coords.y = f->coords.angle_y * (yt - zt) * f->coords.zoom;
	f->coords.z = f->coords.angle_z * (yt + zt) * f->coords.zoom;
	f->coords.z -= f->coords.A[z][y] * f->coords.x_val;
	if (c == 'w')
	{
		f->coords.y1 = f->coords.angle_y * ((yt + 1) - zt) * f->coords.zoom;
		f->coords.z1 = f->coords.angle_z * ((yt + 1) + zt) * f->coords.zoom;
		f->coords.z1 -= f->coords.A[z][y + 1] * f->coords.x_val;
	}
	if (c == 'h')
	{
		f->coords.y1 = f->coords.angle_y * (yt - (zt + 1)) * f->coords.zoom;
		f->coords.z1 = f->coords.angle_z * (yt + (zt + 1)) * f->coords.zoom;
		f->coords.z1 -= f->coords.A[z + 1][y] * f->coords.x_val;
	}
	f->coords.y += (WIN_WIDTH / 2) + f->coords.coord_y;
	f->coords.y1 += (WIN_WIDTH / 2) + f->coords.coord_y;
	f->coords.z += (WIN_HEIGHT / 2) + f->coords.coord_z;
	f->coords.z1 += (WIN_HEIGHT / 2) + f->coords.coord_z;
	draw_lines(f);
}

int	fdf_map(t_fdf *f)
{
	int y;
	int z;

	z = 0;
	f->mlx.img = mlx_new_image(f->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	f->map.data = mlx_get_data_addr(f->mlx.img, &f->map.bp, &f->map.sl, &f->map.end);
	while(f->coords.ys > z)
	{
		y = 0;
		while (f->coords.xs > y)
		{
			f->coords.y = y;
			f->coords.z = z;
			if (f->coords.xs > y + 1)
				draw_map(f, y, z, 'w');
			if (f->coords.ys > z + 1)
				draw_map(f, y, z, 'h');
			y += 1;
		}
		z += 1;
	}
	mlx_put_image_to_window(f->mlx.mlx, f->mlx.win, f->mlx.img, 0, 0);
	mlx_destroy_image(f->mlx.mlx, f->mlx.img);
	return (0);
}
