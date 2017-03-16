#include "fdf.h"

static void	put_pixel(t_fdf *fdf, int y, int z, double uvector)
{
	int		pos;
	int		sign;

	if ((y > 0 && z > 0) && (y < WIN_WIDTH && z < WIN_HEIGHT))
	{
		pos = (y * 4) + (z * WIN_WIDTH * 4);
		sign = (fdf->map.x_val < 0) ? -1 : 1;
		fdf->image.data[pos] = fdf->color.red + uvector;
		fdf->image.data[pos + 1] = fdf->color.green + uvector;
		fdf->image.data[pos + 2] = fdf->color.blue + uvector;
	}
}

static void	draw_lines(t_fdf *fdf)
{
	double y;
	double z;
	double delta_y;
	double delta_z;
	double uvector;

	y = fdf->map.y0;
	z = fdf->map.z0;
	delta_y = fdf->map.y1 - fdf->map.y0;
	delta_z = fdf->map.z1 - fdf->map.z0;
	uvector = sqrt((pow(delta_y, 2)) + (pow(delta_z, 2)));
	delta_y /= uvector;
	delta_z /= uvector;
	while (uvector > 0)
	{
		put_pixel(fdf, y, z, uvector);
		y += delta_y;
		z += delta_z;
		uvector -= 1;
	}
}


static void	draw_map(t_fdf *fdf, int y, int z, char c)
{
	int		yt;
	int		zt;

	yt = y - fdf->map.width / 2;
	zt = z - fdf->map.height / 2;
	fdf->map.y0 = fdf->map.angle_y * (yt - zt) * fdf->map.zoom;
	fdf->map.z0 = fdf->map.angle_z * (yt + zt) * fdf->map.zoom;
	fdf->map.z0 -= fdf->map.val[z][y] * fdf->map.x_val;
	if (c == 'w')
	{
		fdf->map.y1 = fdf->map.angle_y * ((yt + 1) - zt) * fdf->map.zoom;
		fdf->map.z1 = fdf->map.angle_z * ((yt + 1) + zt) * fdf->map.zoom;
		fdf->map.z1 -= fdf->map.val[z][y + 1] * fdf->map.x_val;
	}
	if (c == 'h')
	{
		fdf->map.y1 = fdf->map.angle_y * (yt - (zt + 1)) * fdf->map.zoom;
		fdf->map.z1 = fdf->map.angle_z * (yt + (zt + 1)) * fdf->map.zoom;
		fdf->map.z1 -= fdf->map.val[z + 1][y] * fdf->map.x_val;
	}
	fdf->map.y0 += (WIN_WIDTH / 2) + fdf->map.coordinate_y;
	fdf->map.y1 += (WIN_WIDTH / 2) + fdf->map.coordinate_y;
	fdf->map.z0 += (WIN_HEIGHT / 2) + fdf->map.coordinate_z;
	fdf->map.z1 += (WIN_HEIGHT / 2) + fdf->map.coordinate_z;
	draw_lines(fdf);
}


void	fdf_map(t_fdf *f)
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
				draw_map(fdf, y, z, 'w');
			if (fdf->map.height > z + 1)
				draw_map(fdf, y, z, 'h');
			y += 1;
		}
		z += 1;
	}
}