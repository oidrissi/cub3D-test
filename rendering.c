/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 03:18:46 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/08/02 04:35:54 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render3d(void)
{
	float	i;
	int		j;

	j = 0;
	i = g()->g_player.rotation_angle - (FOV_ANGLE / 2);
	while (i < g()->g_player.rotation_angle + (FOV_ANGLE / 2))
	{
		cast_ray(i);
		putstripe(RAD_ANGLE(normalise_angle(i)), j);
		i += (float)FOV_ANGLE / g()->g_num_rays;
		j++;
	}
}

void	putstripe(float angle, int id)
{
	g()->g_strip.distance = g()->g_ray.distance
		* cos(angle - RAD_ANGLE(g()->g_player.rotation_angle));
	g()->g_strip.distancepp = ((float)g()->g_game_data.res.width / 2)
		/ (float)tan(RAD_ANGLE(FOV_ANGLE) / 2);
	g()->g_strip.wallstripheight = (T_S / g()->g_strip.distance) * g()->g_strip.distancepp;
	g()->g_ray_distance[id] = g()->g_ray.distance;
	react(id, (g()->g_game_data.res.height / 2)
		- (g()->g_strip.wallstripheight / 2)
		+ g()->g_player.view, g()->g_strip.wallstripheight);
}

int	render_frames(void)
{
	if (g()->g_player.walk_direction == 1)
		move_up();
	else if (g()->g_player.walk_direction == -1)
		move_down();
	if (g()->g_player.turn_direction == 1)
		g()->g_player.rotation_angle += 2;
	else if (g()->g_player.turn_direction == -1)
		g()->g_player.rotation_angle -= 2;
	if (g()->g_player.pov_direction == 1)
		move_right();
	else if (g()->g_player.pov_direction == -1)
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
	g()->g_type = 0;
	y = ceiling_filler(x, y, top_pixel);
	xoffset = xoffset_value();
	g()->g_type = 1;
	while (y < top_pixel + wallstripheight && y < g()->g_game_data.res.height)
	{
		yoffset = (y - top_pixel) * ((float)T_S / wallstripheight);
		y = update_walls(x, y, xoffset, yoffset);
	}
	while (y >= 0 && (y < g()->g_game_data.res.height))
	{
		g()->g_type = 2;
		img_update(x, y++, rgbtoint(g()->g_game_data.f.r,
				g()->g_game_data.f.g, g()->g_game_data.f.b));
	}
}
