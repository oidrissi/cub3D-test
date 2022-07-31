/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 03:18:46 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/07/31 20:03:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render3d(void)
{
	float	i;
	int		j;

	j = 0;
	i = g_player.rotation_angle - (FOV_ANGLE / 2);
	while (i < g_player.rotation_angle + (FOV_ANGLE / 2))
	{
		cast_ray(i);
		putstripe(RAD_ANGLE(normalise_angle(i)), j);
		i += (float)FOV_ANGLE / g_num_rays;
		j++;
	}
}

void	putstripe(float angle, int id)
{
	g_strip.distance = g_ray.distance
		* cos(angle - RAD_ANGLE(g_player.rotation_angle));
	g_strip.distancepp = ((float)g_game_data.res.width / 2)
		/ (float)tan(RAD_ANGLE(FOV_ANGLE) / 2);
	g_strip.wallstripheight = (T_S / g_strip.distance) * g_strip.distancepp;
	g_ray_distance[id] = g_ray.distance;
	react(id, (g_game_data.res.height / 2)
		- (g_strip.wallstripheight / 2)
		+ g_player.view, g_strip.wallstripheight);
}

int	render_frames(void)
{
	if (g_player.walk_direction == 1)
		move_up();
	else if (g_player.walk_direction == -1)
		move_down();
	if (g_player.turn_direction == 1)
		g_player.rotation_angle += 2;
	else if (g_player.turn_direction == -1)
		g_player.rotation_angle -= 2;
	if (g_player.pov_direction == 1)
		move_right();
	else if (g_player.pov_direction == -1)
		move_left();
	new_frame();
	return (0);
}

void	react(float x, float top_pixel, float wallstripheight)
{
	int	y;
	int	xoffset;
	int	yoffset;

	y = 0;
	g_type = 0;
	while (y < top_pixel && (y < g_game_data.res.height))
		img_update(x, y++, rgbtoint(g_game_data.c.r,
				g_game_data.c.g, g_game_data.c.b));
	y = ceiling_filler(x, y);
	xoffset = xoffset_value();
	g_type = 1;
	while (y < top_pixel + wallstripheight && y < g_game_data.res.height)
	{
		yoffset = (y - top_pixel) * ((float)T_S / wallstripheight);
		y = update_walls(x, y, xoffset, yoffset);
	}
	while (y >= 0 && (y < g_game_data.res.height))
	{
		g_type = 2;
		img_update(x, y++, rgbtoint(g_game_data.f.r,
				g_game_data.f.g, g_game_data.f.b));
	}
}
