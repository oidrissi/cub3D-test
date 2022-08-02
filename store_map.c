/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 02:50:41 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/08/02 04:58:35 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	last_check(void)
{
	int		i;
	int		j;
	t_data	*m;

	m = g();
	i = 0;
	while (i <= m->g_game_data.map.rows - 1)
	{
		j = 0;
		while ((j < m->g_game_data.map.columns))
		{
			if (m->g_game_data.map.map[j + (i * m->g_game_data.map.columns)] == '\0')
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

static void	store(char ***line)
{
	char	*fre;
	char	*tmp;
	int		i;
	t_data	*m;

	m = g();
	i = 0;
	tmp = (char *)malloc(sizeof(char) * m->g_game_data.map.columns + 1);
	tmp[i] = ' ';
	i++;
	while (***line)
	{
		(tmp[i] = ***line);
		i++;
		(**line)++;
	}
	while (i < m->g_game_data.map.columns)
	{
		(tmp[i] = ' ');
		i++;
	}
	tmp[m->g_game_data.map.columns] = '\0';
	fre = m->g_game_data.map.map;
	m->g_game_data.map.map = ft_strjoin(m->g_game_data.map.map, tmp);
	free(fre);
	free(tmp);
	(*line)++;
}

int	store_map(char ***line)
{
	char	*tmp;
	char	*fre;
	int		i;
	t_data	*m;

	m = g();
	i = 0;
	m->g_game_data.map.map
		= (char *)malloc(sizeof(char) * m->g_game_data.map.columns + 1);
	while (i < m->g_game_data.map.columns)
		m->g_game_data.map.map[i++] = ' ';
	m->g_game_data.map.map[i] = '\0';
	while (**line && (***line == '1' || ***line == ' ' || ***line == '0'))
		store(line);
	i = 0;
	tmp = (char *)malloc(sizeof(char) * m->g_game_data.map.columns + 1);
	while (i < m->g_game_data.map.columns)
		tmp[i++] = ' ';
	tmp[i] = '\0';
	fre = m->g_game_data.map.map;
	m->g_game_data.map.map = ft_strjoin(m->g_game_data.map.map, tmp);
	free(fre);
	free(tmp);
	return (last_check());
}
