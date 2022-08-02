/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:40:45 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/08/02 04:33:08 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_max_w(char *line)
{
	g()->g_game_data.res.width = ft_atoi2(line);
	if (g()->g_game_data.res.width > 2560)
		g()->g_game_data.res.width = 2560;
	else if (g()->g_game_data.res.width < 20)
		g()->g_game_data.res.width = 20;
}

void	check_max_h(char *line)
{
	g()->g_game_data.res.height = ft_atoi2(line);
	if (g()->g_game_data.res.height > 1440)
		g()->g_game_data.res.height = 1440;
	else if (g()->g_game_data.res.height < 20)
		g()->g_game_data.res.height = 20;
}

int	store_resolution(char **line)
{
	int	x;

	x = g()->g_game_data.check;
	if (x == 0x00000001)
	{
		x = x & 0x00000001;
		return (-1);
	}
	*line = skip_blanks(*line);
	if (ft_isdigit(**line))
	{
		g()->g_game_data.check = g()->g_game_data.check | 0x00000001;
		if (helper_resolution(line) == -1)
			return (-1);
	}
	else
		return (-1);
	skip_digits(line);
	*line = skip_blanks(*line);
	if (!ft_strchr("\n \t\0", **line))
		return (-1);
	(line)++;
	return (1);
}

int	fill_f(char **line)
{
	if (ft_isdigit(**line))
		g()->g_game_data.f.r = ft_atoi(*line);
	else
		return (-1);
	if (!(g()->g_game_data.f.r <= 255 && g()->g_game_data.f.r >= 0))
		return (-1);
	skip_digits2(&line);
	if (**line == ',' && (++(*line)) && ft_isdigit(**line))
		g()->g_game_data.f.g = ft_atoi(*line);
	else
		return (-1);
	if (!(g()->g_game_data.f.g <= 255 && g()->g_game_data.f.g >= 0))
		return (-1);
	skip_digits2(&line);
	if (**line == ',' && (++(*line)) && ft_isdigit(**line))
		g()->g_game_data.f.b = ft_atoi(*line);
	else
		return (-1);
	if (!(g()->g_game_data.f.b <= 255 && g()->g_game_data.f.b >= 0))
		return (-1);
	skip_digits2(&line);
	g()->g_game_data.check = g()->g_game_data.check | 0x00000010;
	return (1);
}

int	store_f(char **line)
{
	int	x;
	int	ret;

	ret = 1;
	x = g()->g_game_data.check;
	if (x == 0x00000010)
	{
		x = x & 0x00000010;
		return (-1);
	}
	*line = skip_blanks(*line);
	ret = fill_f(line);
	*line = skip_blanks(*line);
	if (!ft_strchr("\n \t\0", **line))
		return (-1);
	else
		(line)++;
	return (ret);
}
