/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 03:24:04 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/08/02 05:01:44 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_texture(void)
{
	void	*tmp;
	int		useless;
	int		a;
	t_data	*m;

	m = g();
	tmp = mlx_xpm_file_to_image(m->g_mlx_ptr, m->g_game_data.paths.no, &a, &a);
	if (!tmp)
		return (0);
	m->g_textures[0]
		= (unsigned int*)mlx_get_data_addr(tmp, &useless, &useless, &useless);
	free(tmp);
	tmp = mlx_xpm_file_to_image(m->g_mlx_ptr, m->g_game_data.paths.so, &a, &a);
	helper_textures(tmp, useless, a);
	free(tmp);
	return (1);
}

void	free_texture(void)
{
	int	i;
	t_data	*m;

	m = g();
	i = 0;
	while (i < 4)
		if (m->g_textures[i++])
			free(m->g_textures[i]);
}

void	free_sprite(void)
{
	t_data	*m;

	m = g();
	while (m->g_num_spr >= 0)
	{
		if (m->g_spr[m->g_num_spr].img)
			free(m->g_spr[m->g_num_spr].img);
		if (m->g_spr[m->g_num_spr].data)
			free(m->g_spr[m->g_num_spr].data);
		m->g_num_spr--;
	}
}
