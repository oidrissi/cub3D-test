/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:40:57 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/07/30 16:38:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_blanks(char *str)
{
	if (str)
	{
		while (*str == '\t' || *str == ' ')
			str++;
	}
	return (str);
}

int	store_no(char *line)
{
	int	x;

	x = g_game_data.check;
	if (x == 0x00001000)
	{
		x = x & 0x00001000;
		return (-1);
	}
	line = skip_blanks(line);
	g_game_data.paths.no = ft_strtrim(line, " \t");
	if (!g_game_data.paths.no)
		return (-1);
	else
		g_game_data.check = g_game_data.check | 0x00001000;
	return (1);
}

int	store_so(char *line)
{
	int	x;

	x = g_game_data.check;
	if (x == 0x00010000)
	{
		x = x & 0x00010000;
		return (-1);
	}
	line = skip_blanks(line);
	g_game_data.paths.so = ft_strtrim(line, " \t");
	if (!g_game_data.paths.so)
		return (-1);
	else
		g_game_data.check = g_game_data.check | 0x00010000;
	return (1);
}

int	store_we(char *line)
{
	int	x;

	x = g_game_data.check;
	if (x == 0x00100000)
	{
		x = x & 0x00100000;
		return (-1);
	}
	line = skip_blanks(line);
	g_game_data.paths.we = ft_strtrim(line, " \t");
	if (!g_game_data.paths.we)
		return (-1);
	else
		g_game_data.check = g_game_data.check | 0x00100000;
	return (1);
}

int	store_ea(char *line)
{
	int	x;

	x = g_game_data.check;
	if (x == 0x01000000)
	{
		x = (x & 0x01000000);
		return (-1);
	}
	line = skip_blanks(line);
	g_game_data.paths.ea = ft_strtrim(line, " \t");
	if (!g_game_data.paths.ea)
		return (-1);
	else
		g_game_data.check = g_game_data.check | 0x01000000;
	return (1);
}
