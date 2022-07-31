/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:41:14 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/07/30 16:38:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_p(char *map, int *p)
{
	int	i;
	int	j;

	i = 0;
	while (i < g_game_data.map.rows)
	{
		j = 0;
		while (j < g_game_data.map.columns)
		{
			if (ft_strchr("NWES", map[j
						+ (i * g_game_data.map.columns)]) != NULL)
				(*p)++;
			j++;
		}
		i++;
	}
}

int	check_all(char *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < g_game_data.map.rows)
	{
		j = 0;
		while (j < g_game_data.map.columns)
		{
			if (ft_strchr("NWES01234", map[j
						+ (i * g_game_data.map.columns)]) == NULL)
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}
