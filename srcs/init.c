/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:57:46 by mishin            #+#    #+#             */
/*   Updated: 2022/01/19 19:14:01 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_mlx_img(t_param *p)
{
	p->img3d.img = mlx_new_image(p->mlx, SCREENWIDTH, SCREENHEIGHT);
	if (!p->img3d.img)
		exit(1);
	p->img3d.data = (int *)mlx_get_data_addr(p->img3d.img, &p->img3d.bpp, \
										&p->img3d.linesize, &p->img3d.endian);
}

//NOTE: buffer	=> 직관적으로 생각할 수 있는 2차원 배열 형태
static int	init_buffer(t_param *p)
{
	int	i;

	p->buf3d = (int **)calloc_(SCREENHEIGHT, sizeof(int *));
	i = -1;
	while (++i < SCREENHEIGHT)
		p->buf3d[i] = (int *)calloc_(SCREENWIDTH, sizeof(int));
	return (0);
}

void	init(t_param *p)
{
	p->mlx = mlx_init();
	if (!p->mlx)
		exit(1);
	p->win = mlx_new_window(p->mlx, SCREENWIDTH, SCREENHEIGHT, "Raycaster");
	if (!p->win)
		exit(1);
	init_config(p->cfg);
	print_config(p->cfg);
	init_buffer(p);
	init_mlx_img(p);
	load_imgs(p);
	imgs_to_textures(p);
}
