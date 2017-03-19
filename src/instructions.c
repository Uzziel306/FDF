/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 02:31:14 by asolis            #+#    #+#             */
/*   Updated: 2017/03/19 02:31:18 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	drawing_instructions(void)
{
	ft_putstr("|----|FDF --------- MENU|-----|\n");
	ft_putstr("|-----------------------------|\n");
	ft_putstr("|Insert the RGB color.        |\n");
	ft_putstr("|EXAMPLE R: 234, G:143, B: 456|\n");
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
	ft_putstr("|Press 'V' to delete colors.  |\n");
	ft_putstr("|-----------------------------|\n");
}

void	drawing_instructions2(void)
{
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
	ft_putstr("|Press 'Q' to increase the map|\n");
	ft_putstr("|-----------------------------|\n");
	ft_putstr("|Press 'E' to sink the map    |\n");
	ft_putstr("|-----------------------------|\n");
	ft_putstr("|Press 'ESC to exit and close |\n");
	ft_putstr("|the window.                  |\n");
	ft_putstr("|-----------------------------|\n");
}
