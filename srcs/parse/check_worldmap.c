/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_worldMap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:16:47 by mishin            #+#    #+#             */
/*   Updated: 2022/01/19 13:45:42 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_worldmap(t_param *p, t_config *cfg)
{
	int	y;
	int	x;
	int	player;

	y = 0;
	player = 0;
	while (y < cfg->mapheight)
	{
		x = 0;
		while (x < cfg->mapwidth)
		{
			if (!check_val(p->worldmap[y][x]))
				err_exit("invalid val in map", p);
			if (check_val(p->worldmap[y][x]) == PLAYER)
				player += (set_dir(p, p->worldmap[y][x]) && set_pos(p, x, y));
			x++;
		}
		y++;
	}
	if (player != 1)
		err_exit("wrong player numer", p);
	check_map_leaks(p, p->worldmap);
}
