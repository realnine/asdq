/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:15:45 by mishin            #+#    #+#             */
/*   Updated: 2022/01/19 17:36:23 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//NOTE: t_img		=> mlx에서 사용되는 1차원 배열 형태 (width * y + x)
static void	load_file(t_param *p, t_img *I, char *filename)
{
	int			ext;
	t_loadfunc	f;

	printf("loading %s...\n", filename);
	f = NULL;
	ext = ft_strlen(filename) - 3;
	if (ft_strncmp(&filename[ext], "xpm", 3) == 0)
		f = mlx_xpm_file_to_image;
	else if (ft_strncmp(&filename[ext], "png", 3) == 0)
		f = mlx_png_file_to_image;
	else
		err_exit_(formatstr("not supported extension: {}", \
			&filename[ext], 0), p);
	I->img = f(p->mlx, filename, &I->width, &I->height);
	if (!I->img)
		err_exit_(formatstr("{}: load failed", filename, 0), p);
	I->data = (int *)mlx_get_data_addr(I->img, &I->bpp, \
									&I->linesize, &I->endian);
	if (I->width != I->height || I->width != TEXWIDTH)
		err_exit_(formatstr("{}: 256x256 image required.", filename, 0), p);
	printf("%s loaded\n", filename);
}

void	load_imgs(t_param *p)
{
	load_file(p, &p->wall_n, p->tex_path[N]);
	load_file(p, &p->wall_s, p->tex_path[S]);
	load_file(p, &p->wall_w, p->tex_path[W]);
	load_file(p, &p->wall_e, p->tex_path[E]);
}

void	clear_img(t_img img, int w, int h)
{
	int	x;
	int	y;

	y = -1;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
			img.data[(y * img.linesize / sizeof(int) + x)] = 0;
	}
}
