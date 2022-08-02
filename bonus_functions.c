/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 03:56:39 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/08/02 04:50:47 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_args(int ac, char **av)
{
	char	*s;
	t_data	*m;

	m = g();
	s = ft_strrchr(av[1], '.');
	if ((ft_strlen(s) != 4 || !ft_comp(s + 1, "cub"))
		&& write(2, "No .cub file extension\n", 23))
		exit(0);
	init_game();
	init_player_pos();
	sp_pos();
	if (!fill_texture() && write(2, "error loading textures\n", 22))
		exit(0);
	m->g_argc = ac;
	if (m->g_argc == 3)
	{
		if ((ft_strlen(av[2]) != 6 || !ft_comp(av[2], "--save"))
			&& write(2, "Wrong second argument\n", 22))
			exit(0);
		else
			save_img();
	}
	system("afplay music/Buttercup-Melody.wav &>/dev/null &");
	m->g_start_time = clock();
	m->g_win_ptr = mlx_new_window(m->g_mlx_ptr, m->g_game_data.res.width,
			m->g_game_data.res.height, "cub3D");
}

void	byebye(void)
{
	t_data	*m;

	m = g();
	if (m->g_fre)
		free(m->g_fre);
	free_sprite();
	system("killall afplay");
	exit(0);
}

void	play_music(void)
{
	clock_t	current_time;
	t_data	*m;

	m = g();
	current_time = clock();
	if (((double)(current_time - m->g_start_time)
		/ (double)CLOCKS_PER_SEC) >= 66)
	{
		system("killall afplay");
		system("afplay music/Buttercup-Melody.wav &>/dev/null &");
		m->g_start_time = current_time;
	}
}

void	sp_pos(void)
{
	int		i;
	int		j;
	t_data	*m;

	i = -1;
	m = g();
	ft_bzero(&m->g_spr, sizeof(m->g_spr));
	while ((++i < m->g_game_data.map.rows))
	{
		j = -1;
		while (++j < m->g_game_data.map.columns && m->g_num_spr < NBR_SPR)
		{
			if (m->g_game_data.map.map[j + (i * m->g_game_data.map.columns)] == '2'
				|| m->g_game_data.map.map[j + (i * m->g_game_data.map.columns)] == '3'
				|| m->g_game_data.map.map[j
					+ (i * m->g_game_data.map.columns)] == '4')
			{
				m->g_spr[m->g_num_spr].x = j * T_S + T_S / 2;
				m->g_spr[m->g_num_spr].y = i * T_S + T_S / 2;
				init_sprite(m->g_num_spr++,
					m->g_game_data.map.map[j + (i * m->g_game_data.map.columns)]);
			}
		}
	}
}

int	check_stuff(char *map, int i, int j, int *p)
{
	t_data	*m;

	m = g();
	if (ft_strchr("NSWE", map[j
				+ (i * m->g_game_data.map.columns)]))
		*p = (*p) + 1;
	if (!ft_strchr(" 01234NSEW", map[j
				+ (i * m->g_game_data.map.columns)]))
		return (1);
	if (ft_strchr("0234NSEW", map[j
				+ (i * m->g_game_data.map.columns)]))
	{
		if (map[j + 1 + (i * m->g_game_data.map.columns)] == ' '
			|| map[j - 1 + (i * m->g_game_data.map.columns)] == ' '
			|| map[j + ((i + 1) * m->g_game_data.map.columns)] == ' '
			|| map[j + ((i - 1) * m->g_game_data.map.columns)] == ' ')
			return (1);
	}
	else
	{
		if (map[(j + 1) + ((i + 1) * m->g_game_data.map.columns)] == '0'
			|| map[(j - 1) + ((i - 1) * m->g_game_data.map.columns)] == '0'
			|| map[(j + 1) + ((i - 1) * m->g_game_data.map.columns)] == '0'
			|| map[(j - 1) + ((i + 1) * m->g_game_data.map.columns)] == '0')
			map[j + (i * m->g_game_data.map.columns)] = '1';
	}
	return (0);
}
