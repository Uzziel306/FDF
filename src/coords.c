/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 15:29:08 by asolis            #+#    #+#             */
/*   Updated: 2017/03/15 15:29:09 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_strl(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if(((str[i] >= '0' && str[i] <= '9') && str[i + 1] == ' '))
			j++;
		else if(((str[i] >= '0' && str[i] <= '9') && str[i + 1] == '\n'))
			j++;
		else if(((str[i] >= '0' && str[i] <= '9') && str[i  + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

int	getting_k(char *str, int *A)
{
	t_coords b;

	b.k = 0;
	b.i = -1;
	b.j = 0;
	b.tempchr = ft_strnew(0);
	b.ret = ft_strl(str);
	str[b.ret] = ' ';
	while(str[++b.i])
	{
		if(ft_isdigit(str[b.i]) || str[b.i] == '-')
			b.tempchr[b.j++] = str[b.i];
		else if((str[b.i] == ' ' || str[b.i] == '\n') && (ft_isdigit(str[b.i + 1]) || str[b.i + 1] == '-' || str[b.i + 1] == '\0'))
		{
			A[b.k] = ft_atoi(b.tempchr);
			b.tempchr = ft_strnew(0);
			b.j = 0;
			b.k++;
		}
	}
	return(b.ret);
}

void	coordinates(int fd, t_fdf *f, char *argv)
{
	t_coords	a;
	char			*line;
	int				z;

	z = 0;
	a.i = 0;
	while (get_next_line(fd, &line))
	{
		f->coords.i = ft_strl(line);
		f->coords.j += 1;
	}
	close(fd);
	fd = open(argv, O_RDONLY);
	f->coords.A = (int**)malloc(sizeof(int*) *(f->coords.j));

	while (get_next_line(fd, &a.str) && z <= f->coords.j)
	{
		f->coords.A[z] = (int*)malloc(sizeof(int) *(f->coords.i));
		a.ret = getting_k(a.str, f->coords.A[a.i]);
		a.i++;
		z++;
	}
	printf("x : %d\ny : %d\n", a.ret, a.i);
	f->coords.xs = a.ret;
	f->coords.ys = a.i;
}
