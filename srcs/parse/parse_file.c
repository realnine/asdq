/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:16:34 by mishin            #+#    #+#             */
/*   Updated: 2022/01/19 16:33:54 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	malloc_worldmap(t_param *p)
{
	int	i;

	p->worldmap = (int **)calloc_(p->cfg->mapheight, sizeof(int *));
	i = 0;
	while (i < p->cfg->mapheight)
		p->worldmap[i++] = (int *)calloc_(p->cfg->mapwidth, sizeof(int));
}

void	fill_worldmap(t_param *p)
{
	int		y;
	int		x;
	t_lst	*tmp;

	malloc_worldmap(p);
	y = -1;
	tmp = p->map;
	while (++y < p->cfg->mapheight)
	{
		x = -1;
		while (++x < p->cfg->mapwidth)
		{
			if (tmp->content[x] == '\0')
			{
				while (x < p->cfg->mapwidth)
					p->worldmap[y][x++] = ' ';
				break ;
			}
			if (ft_isdigit(tmp->content[x]))
				p->worldmap[y][x] = tmp->content[x] - 48;
			else
				p->worldmap[y][x] = tmp->content[x];
		}
		tmp = tmp->next;
	}
}

void	filename_check(char *filename, char *extension, t_param *p)
{
	int	f_len;
	int	e_len;

	f_len = ft_strlen(filename);
	e_len = ft_strlen(extension);
	if (f_len <= e_len)
		err_exit("invalid filename", p);
	if (ft_strncmp(filename + f_len - e_len, extension, e_len) != 0)
		err_exit("invalid extension", p);
}

void	cnt_mapheight(t_param *p)
{
	t_lst	*tail;
	int		cnt;

	cnt = 0;
	tail = lst_get_tail(p->map);
	while (tail)
	{
		if (is_empty_line(tail->content))
		{
			cnt++;
			tail = tail->prev;
		}
		else
			break ;
	}
	p->cfg->mapheight = lst_get_len(p->map) - cnt;
}

void	parse_file(t_param *p, char *filename)
{
	char	*line;
	int		ret;
	int		fd;

	filename_check(filename, ".cub", p);
	fd = open(filename, O_RDONLY);
	if (fd < 3)
		err_exit("open() failure", p);
	p->cfg->mapwidth = 0;
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		parse_line(p, line);
		free(line);
		line = NULL;
		ret = get_next_line(fd, &line);
	}
	if (ret == -1)
		err_exit("get_next_line failure", p);
	parse_line(p, line);
	free(line);
	close(fd);
	cnt_mapheight(p);
	fill_worldmap(p);
}
// 55 ????????? .cub ?????? ??????????????? ????????? ????????? ?????? 0
// 57 str??? ????????? 4??????, end 4????????? ?????? (????????? 1, ????????? 0 ??????)
// 66 ??????????????? ?????????(.cub)??? ??????????????? ??????
// 71 ????????? ???????????? 0???, ????????? 1???, ????????? -1??? ????????????
