/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 04:09:49 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/08/02 05:00:27 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	byebye(void)
{
	t_data	*m;

	m = g();
	if (m->g_fre)
		free(m->g_fre);
	free_sprite();
	exit(0);
}

void	sp_pos(void)
{
	int	i;
	int	j;
	t_data	*m;

	m = g();
	i = -1;
	ft_bzero(&m->g_spr, sizeof(m->g_spr));
	while ((++i < m->g_game_data.map.rows))
	{
		j = -1;
		while (++j < m->g_game_data.map.columns && m->g_num_spr < NBR_SPR)
		{
			if (m->g_game_data.map.map[j + (i * m->g_game_data.map.columns)] == '2')
			{
				m->g_spr[m->g_num_spr].x = j * T_S + T_S / 2;
				m->g_spr[m->g_num_spr].y = i * T_S + T_S / 2;
				init_sprite(m->g_num_spr++,
					m->g_game_data.map.map[j + (i * m->g_game_data.map.columns)]);
			}
		}
	}
}

void	init_sprite(int i, char type)
{
	int		a;
	t_data	*m;

	m = g();
	if (type == '2')
		m->g_spr[i].img
			= mlx_xpm_file_to_image(m->g_mlx_ptr, m->g_game_data.paths.s, &a, &a);
	if (!m->g_spr[i].img && write(2, "sprite error", 12))
		exit(0);
	m->g_spr[i].data = (int *)mlx_get_data_addr(m->g_spr[i].img, &a, &a, &a);
}

void	new_frame(void)
{
	t_data	*m;

	m = g();
	mlx_destroy_image(m->g_mlx_ptr, m->g_img.img_ptr);
	m->g_img.img_ptr = mlx_new_image(m->g_mlx_ptr, m->g_game_data.res.width,
			m->g_game_data.res.height);
	m->g_img.addr = (int *)mlx_get_data_addr(m->g_img.img_ptr, &m->g_img.bpp,
			&m->g_img.line_length, &m->g_img.endian);
	render3d();
	sp_sort_dist();
	sprites();
	if (m->g_argc == 2)
		mlx_put_image_to_window(m->g_mlx_ptr, m->g_win_ptr, m->g_img.img_ptr, 0, 0);
}

void	img_update(int x, int y, int color)
{
	t_data	*m;

	m = g();
	if (x >= 0 && x < m->g_game_data.res.width && y >= 0
		&& y < m->g_game_data.res.height)
		m->g_img.addr[(x + (y * m->g_game_data.res.width))] = color;
}
