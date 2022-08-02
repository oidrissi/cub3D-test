/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 03:38:07 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/08/02 05:03:04 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*ft_assign(int cf, int cd, char const *s)
{
	char	*ret;

	ret = NULL;
	if (cf >= (int)ft_strlen(s))
	{
		ret = (char *)malloc(1);
		if (!ret)
			return (NULL);
		*ret = '\0';
		return (ret);
	}
	else if ((cf + cd) != 0 && cf != (int)ft_strlen(s))
	{
		ret = (char *)ft_calloc(ft_strlen(s)
				- (cd + cf) + 1, sizeof(char));
		if (ret)
			ft_strlcpy(ret, (s + cd), (ft_strlen(s) - (cd + cf)) + 1);
	}
	else
		ret = ft_strdup(s);
	return (ret);
}

char	*ft_strtrim(char const *s, char const *set)
{
	int		len;
	int		cd;
	int		cf;

	if (!s)
		return (NULL);
	if (!set)
		return (ft_strdup(s));
	cd = 0;
	cf = 0;
	len = (ft_strlen(s) - 1);
	while (ft_strchr(set, s[cd]))
		cd++;
	while (ft_strchr(set, s[len]))
	{
		len--;
		cf++;
	}
	return (ft_assign(cf, cd, s));
}

int	map_size(char **line)
{
	char	**save;
	int		i;
	t_data	*m;

	m = g();
	save = line;
	m->g_game_data.map.columns = 0;
	m->g_game_data.map.rows = 1;
	i = 0;
	while (*save)
	{
		i = ft_strlen(*save);
		if (i > m->g_game_data.map.columns)
			m->g_game_data.map.columns = i;
		m->g_game_data.map.rows++;
		save++;
	}
	m->g_game_data.map.columns += 2;
	return (1);
}

int	helper_textures(void *tmp, int useless, int a)
{
	t_data	*m;

	m = g();
	if (!(tmp))
		return (0);
	m->g_textures[1]
		= (unsigned int*)mlx_get_data_addr(tmp, &useless, &useless, &useless);
	free(tmp);
	tmp = mlx_xpm_file_to_image(m->g_mlx_ptr, m->g_game_data.paths.we, &a, &a);
	if (!(tmp))
		return (0);
	m->g_textures[2]
		= (unsigned int*)mlx_get_data_addr(tmp, &useless, &useless, &useless);
	free(tmp);
	tmp = mlx_xpm_file_to_image(m->g_mlx_ptr, m->g_game_data.paths.ea, &a, &a);
	if (!(tmp))
		return (0);
	m->g_textures[3]
		= (unsigned int*)mlx_get_data_addr(tmp, &useless, &useless, &useless);
	return (1);
}

int	player_rotation_angle(int i, int j)
{
	t_data	*m;

	m = g();
	if (m->g_game_data.map.map[j + (i * m->g_game_data.map.columns)] == 'N')
	{
		m->g_player.rotation_angle = 270;
		return (1);
	}
	else if (m->g_game_data.map.map[j + (i * m->g_game_data.map.columns)]
		== 'S')
	{
		m->g_player.rotation_angle = 90;
		return (1);
	}
	else if (m->g_game_data.map.map[j + (i * m->g_game_data.map.columns)]
		== 'E')
	{
		m->g_player.rotation_angle = 0;
		return (1);
	}
	else if (m->g_game_data.map.map[j + (i * m->g_game_data.map.columns)]
		== 'W')
	{
		m->g_player.rotation_angle = 180;
		return (1);
	}
	return (0);
}
