/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 03:24:04 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/07/30 19:39:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_texture(void)
{
	void	*tmp;
	int		useless;
	int		a;

	tmp = mlx_xpm_file_to_image(g_mlx_ptr, g_game_data.paths.no, &a, &a);
	if (!tmp)
		return (0);
	g_textures[0]
		= (unsigned int*)mlx_get_data_addr(tmp, &useless, &useless, &useless);
	free(tmp);
	tmp = mlx_xpm_file_to_image(g_mlx_ptr, g_game_data.paths.so, &a, &a);
	helper_textures(tmp, useless, a);
	free(tmp);
	return (1);
}

void	free_texture(void)
{
	int	i;

	i = 0;
	while (i < 4)
		if (g_textures[i++])
			free(g_textures[i]);
}

void	free_sprite(void)
{
	while (g_num_spr >= 0)
	{
		if (g_spr[g_num_spr].img)
			free(g_spr[g_num_spr].img);
		if (g_spr[g_num_spr].data)
			free(g_spr[g_num_spr].data);
		g_num_spr--;
	}
}
