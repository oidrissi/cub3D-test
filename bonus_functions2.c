/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_functions2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 04:27:48 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/08/03 14:25:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite(int i, char type)
{
	int		a;
	t_data	*m;

	m = g();
	if (type == '2')
		m->g_spr[i].img
			= mlx_xpm_file_to_image(m->g_mlx_ptr,
				m->g_game_data.paths.s, &a, &a);
	else if (type == '3')
		m->g_spr[i].img
			= mlx_xpm_file_to_image(m->g_mlx_ptr,
				m->g_game_data.paths.s1, &a, &a);
	else if (type == '4')
		m->g_spr[i].img
			= mlx_xpm_file_to_image(m->g_mlx_ptr,
				m->g_game_data.paths.s2, &a, &a);
	if (!m->g_spr[i].img && write(2, "sprite error", 12))
		byebye();
	m->g_spr[i].data = (int *)mlx_get_data_addr(m->g_spr[i].img,
			&a, &a, &a);
}

void	new_frame(void)
{
	t_data	*m;

	m = g();
	if (m->g_argc == 2)
		mlx_destroy_image(m->g_mlx_ptr, m->g_img.img_ptr);
	m->g_img.img_ptr = mlx_new_image(m->g_mlx_ptr, m->g_game_data.res.width,
			m->g_game_data.res.height);
	m->g_img.addr = (int *)mlx_get_data_addr(m->g_img.img_ptr, &m->g_img.bpp,
			&m->g_img.line_length, &m->g_img.endian);
	render3d();
	sp_sort_dist();
	sprites();
	play_music();
	if (m->g_argc == 2)
		mlx_put_image_to_window(m->g_mlx_ptr,
			m->g_win_ptr, m->g_img.img_ptr, 0, 0);
}

int	shadows(unsigned int color, int y, int x)
{
	t_color		old_color;
	float		ratio;
	t_data		*m;

	m = g();
	ratio = 0;
	if (m->g_type == 1)
		ratio = (m->g_ray_distance[x] * 100
				/ m->g_game_data.res.height / 100.0);
	else if (m->g_type == 0)
		ratio = (y * 100 / ((m->g_game_data.res.height / 2)
					+ m->g_player.view) / 100.0);
	else if (m->g_type == 2)
		ratio = ((m->g_game_data.res.height / 2)
				+ m->g_player.view) / (float)y;
	else if (m->g_type == 3)
		ratio = m->g_spr[m->g_spr_id].distance * 100
			/ m->g_game_data.res.width / 100.0;
	(ratio > 1) && (ratio = 1);
	(ratio < 0) && (ratio = 0);
	ratio *= 1;
	old_color.r = (color & 0x00ff0000) >> 16;
	old_color.g = (color & 0x0000ff00) >> 8;
	old_color.b = (color & 0x000000ff);
	return (rgbtoint((1 - ratio) * old_color.r + ratio * 0,
			(1 - ratio) * old_color.g + ratio * 0,
			(1 - ratio) * old_color.b + ratio * 0));
}

void	img_update(int x, int y, int color)
{
	t_data	*m;

	m = g();
	if (x >= 0 && x < m->g_game_data.res.width && y >= 0
		&& y < m->g_game_data.res.height)
		m->g_img.addr[(x
				+ (y * m->g_game_data.res.width))] = shadows(color, y, x);
}
