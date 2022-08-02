/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 04:07:18 by marvin            #+#    #+#             */
/*   Updated: 2022/07/31 04:07:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	helper_resolution(char **line)
{
	check_max_w(*line);
	skip_digits(line);
	*line = skip_blanks(*line);
	if (ft_isdigit(**line))
		check_max_h(*line);
	else
		return (-1);
	return (1);
}

int	xoffset_value(void)
{
	if (g()->g_ray.washitvertical)
		return ((int)g()->g_ray.wallhity % T_S);
	else
		return ((int)g()->g_ray.wallhitx % T_S);
}

int	update_walls(int x, int y, int xoffset, int yoffset)
{
	if (g()->g_ray.rayleft && g()->g_ray.washitvertical)
		img_update(x, y++, g()->g_textures[2][(yoffset * T_S) + xoffset]);
	else if (g()->g_ray.rayright && g()->g_ray.washitvertical)
		img_update(x, y++, g()->g_textures[3][(yoffset * T_S) + xoffset]);
	else if (g()->g_ray.rayup && !g()->g_ray.washitvertical)
		img_update(x, y++, g()->g_textures[0][(yoffset * T_S) + xoffset]);
	else if (g()->g_ray.raydown && !g()->g_ray.washitvertical)
		img_update(x, y++, g()->g_textures[1][(yoffset * T_S) + xoffset]);
	return (y);
}

int	ceiling_filler(int x, int y, float top_pixel)
{
	while (y < top_pixel && (y < g()->g_game_data.res.height))
		img_update(x, y++, rgbtoint(g()->g_game_data.c.r,
				g()->g_game_data.c.g, g()->g_game_data.c.b));
	return (y);
}

t_data	*g(void)
{
	static t_data	data;

	return (&data);
}
