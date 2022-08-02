/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 03:20:40 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/08/02 04:34:18 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_pos(void)
{
	int	i;
	int	j;

	i = -1;
	while (++i < g()->g_game_data.map.rows)
	{
		j = -1;
		while (++j < g()->g_game_data.map.columns)
		{
			g()->g_player.x = (j + 0.5) * T_S;
			g()->g_player.y = (i + 0.5) * T_S;
			if (player_rotation_angle(i, j))
				return ;
		}
	}
}

void	move_up(void)
{
	float	new_x;
	float	new_y;

	new_x = cos(g()->g_player.rotation_angle * RAD) * g()->g_speed;
	new_y = sin(g()->g_player.rotation_angle * RAD) * g()->g_speed;
	if (!iswall(g()->g_player.x + new_x * 4, g()->g_player.y + new_y * 4)
		&& !is_sprite(g()->g_player.x + new_x * 4, g()->g_player.y + new_y * 4))
	{
		g()->g_player.x += new_x;
		g()->g_player.y += new_y;
	}
}

void	move_down(void)
{
	float	new_x;
	float	new_y;

	new_x = cos(g()->g_player.rotation_angle * RAD) * g()->g_speed;
	new_y = sin(g()->g_player.rotation_angle * RAD) * g()->g_speed;
	if (!iswall(g()->g_player.x - new_x * 4, g()->g_player.y - new_y * 4)
		&& !is_sprite(g()->g_player.x - new_x * 4, g()->g_player.y - new_y * 4))
	{
		g()->g_player.x -= new_x;
		g()->g_player.y -= new_y;
	}
}

void	move_right(void)
{
	float	new_x;
	float	new_y;

	new_x = cos(g()->g_player.rotation_angle * RAD) * g()->g_speed;
	new_y = sin(g()->g_player.rotation_angle * RAD) * g()->g_speed;
	new_x = cos((g()->g_player.rotation_angle + 90) * RAD) * g()->g_speed;
	new_y = sin((g()->g_player.rotation_angle + 90) * RAD) * g()->g_speed;
	if (!iswall(g()->g_player.x + new_x * 2, g()->g_player.y + new_y * 2)
		&& !is_sprite(g()->g_player.x + new_x * 2, g()->g_player.y + new_y * 2))
	{
		g()->g_player.x += new_x;
		g()->g_player.y += new_y;
	}
}

void	move_left(void)
{
	float	new_x;
	float	new_y;

	new_x = cos(g()->g_player.rotation_angle * RAD) * g()->g_speed;
	new_y = sin(g()->g_player.rotation_angle * RAD) * g()->g_speed;
	new_x = cos((g()->g_player.rotation_angle + 90) * RAD) * g()->g_speed;
	new_y = sin((g()->g_player.rotation_angle + 90) * RAD) * g()->g_speed;
	if (!iswall(g()->g_player.x - new_x * 2, g()->g_player.y - new_y * 2)
		&& !is_sprite(g()->g_player.x - new_x * 2, g()->g_player.y - new_y * 2))
	{
		g()->g_player.x -= new_x;
		g()->g_player.y -= new_y;
	}
}
