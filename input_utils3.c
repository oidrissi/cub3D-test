/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:40:57 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/08/02 04:57:01 by ael-ghem         ###   ########.fr       */
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
	t_data	*m;

	m = g();
	x = m->g_game_data.check;
	if (x == 0x00001000)
	{
		x = x & 0x00001000;
		return (-1);
	}
	line = skip_blanks(line);
	m->g_game_data.paths.no = ft_strtrim(line, " \t");
	if (!m->g_game_data.paths.no)
		return (-1);
	else
		m->g_game_data.check = m->g_game_data.check | 0x00001000;
	return (1);
}

int	store_so(char *line)
{
	int	x;
	t_data	*m;

	m = g();
	x = m->g_game_data.check;
	if (x == 0x00010000)
	{
		x = x & 0x00010000;
		return (-1);
	}
	line = skip_blanks(line);
	m->g_game_data.paths.so = ft_strtrim(line, " \t");
	if (!m->g_game_data.paths.so)
		return (-1);
	else
		m->g_game_data.check = m->g_game_data.check | 0x00010000;
	return (1);
}

int	store_we(char *line)
{
	int	x;
	t_data	*m;

	m = g();
	x = m->g_game_data.check;
	if (x == 0x00100000)
	{
		x = x & 0x00100000;
		return (-1);
	}
	line = skip_blanks(line);
	m->g_game_data.paths.we = ft_strtrim(line, " \t");
	if (!m->g_game_data.paths.we)
		return (-1);
	else
		m->g_game_data.check = m->g_game_data.check | 0x00100000;
	return (1);
}

int	store_ea(char *line)
{
	int	x;
	t_data	*m;

	m = g();
	x = m->g_game_data.check;
	if (x == 0x01000000)
	{
		x = (x & 0x01000000);
		return (-1);
	}
	line = skip_blanks(line);
	m->g_game_data.paths.ea = ft_strtrim(line, " \t");
	if (!m->g_game_data.paths.ea)
		return (-1);
	else
		m->g_game_data.check = m->g_game_data.check | 0x01000000;
	return (1);
}
