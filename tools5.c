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

int	xoffset_value(int xoffset)
{
	if (g_ray.washitvertical)
		xoffset = (int)g_ray.wallhity % T_S;
	else
		xoffset = (int)g_ray.wallhitx % T_S;
	return (xoffset);
}

int	update_walls(int x, int y, int xoffset, int yoffset)
{
	if (g_ray.rayleft && g_ray.washitvertical)
		img_update(x, y++, g_textures[2][(yoffset * T_S) + xoffset]);
	else if (g_ray.rayright && g_ray.washitvertical)
		img_update(x, y++, g_textures[3][(yoffset * T_S) + xoffset]);
	else if (g_ray.rayup && !g_ray.washitvertical)
		img_update(x, y++, g_textures[0][(yoffset * T_S) + xoffset]);
	else if (g_ray.raydown && !g_ray.washitvertical)
		img_update(x, y++, g_textures[1][(yoffset * T_S) + xoffset]);
	return (y);
}