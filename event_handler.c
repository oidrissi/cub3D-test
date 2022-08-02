/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 03:17:03 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/08/02 04:33:08 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	iswall(float x, float y)
{
	int	xtemp;
	int	ytemp;

	xtemp = (int)floor(x / T_S);
	ytemp = (int)floor(y / T_S);
	if (xtemp <= g()->g_game_data.map.columns && xtemp >= 0
		&& ytemp <= g()->g_game_data.map.rows && ytemp >= 0)
		return ((g()->g_game_data.map.map[xtemp
					+ (ytemp * g()->g_game_data.map.columns)] == '1')
			|| g()->g_game_data.map.map[
				xtemp + (ytemp * g()->g_game_data.map.columns)] == ' ');
	return (0);
}

int	is_sprite(float x, float y)
{
	int	xtemp;
	int	ytemp;

	xtemp = (int)floor(x / T_S);
	ytemp = (int)floor(y / T_S);
	if (xtemp <= g()->g_game_data.map.columns && xtemp >= 0
		&& ytemp <= g()->g_game_data.map.rows && ytemp >= 0)
		return (g()->g_game_data.map.map[xtemp
				+ (ytemp * g()->g_game_data.map.columns)] == '2'
			|| g()->g_game_data.map.map[xtemp + (ytemp
					* g()->g_game_data.map.columns)] == '3'
			|| g()->g_game_data.map.map[xtemp + (ytemp
					* g()->g_game_data.map.columns)] == '4');
	return (0);
}

int	key_pressed(int key)
{
	if (key == W_KEY)
		g()->g_player.walk_direction = 1;
	if (key == UP_KEY && g()->g_player.view < g()->g_game_data.res.height / 4)
		g()->g_player.view += g()->g_game_data.res.height / 40;
	if (key == DOWN_KEY && g()->g_player.view > -g()->g_game_data.res.height / 4)
		g()->g_player.view -= g()->g_game_data.res.height / 40;
	if (key == S_KEY)
		g()->g_player.walk_direction = -1;
	if (key == LEFT_KEY)
		g()->g_player.turn_direction = -1;
	if (key == RIGHT_KEY)
		g()->g_player.turn_direction = 1;
	if (key == A_KEY)
		g()->g_player.pov_direction = -1;
	if (key == D_KEY)
		g()->g_player.pov_direction = 1;
	if (key == ESC)
		byebye();
	return (0);
}

int	key_released(int key)
{
	if (key == W_KEY || key == S_KEY)
		g()->g_player.walk_direction = 0;
	if (key == LEFT_KEY || key == RIGHT_KEY)
		g()->g_player.turn_direction = 0;
	if (key == A_KEY || key == D_KEY)
		g()->g_player.pov_direction = 0;
	return (0);
}
