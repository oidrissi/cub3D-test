/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 03:38:07 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/07/30 20:52:33 by marvin           ###   ########.fr       */
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

	save = line;
	g_game_data.map.columns = 0;
	g_game_data.map.rows = 1;
	i = 0;
	while (*save)
	{
		i = ft_strlen(*save);
		if (i > g_game_data.map.columns)
			g_game_data.map.columns = i;
		g_game_data.map.rows++;
		save++;
	}
	g_game_data.map.columns += 2;
	return (1);
}

void	helper_textures(void *tmp, int useless, int a)
{
	if (!(tmp))
		return (0);
	g_textures[1]
		= (unsigned int*)mlx_get_data_addr(tmp, &useless, &useless, &useless);
	free(tmp);
	tmp = mlx_xpm_file_to_image(g_mlx_ptr, g_game_data.paths.we, &a, &a);
	if (!(tmp))
		return (0);
	g_textures[2]
		= (unsigned int*)mlx_get_data_addr(tmp, &useless, &useless, &useless);
	free(tmp);
	tmp = mlx_xpm_file_to_image(g_mlx_ptr, g_game_data.paths.ea, &a, &a);
	if (!(tmp))
		return (0);
	g_textures[3]
		= (unsigned int*)mlx_get_data_addr(tmp, &useless, &useless, &useless);
}

void	player_rotation_angle(void)
{
	if ((g_game_data.map.map[j + (i * g_game_data.map.columns)] == 'N'))
	{
		g_player.rotation_angle = 270;
		return ;
	}
	else if ((g_game_data.map.map[j + (i * g_game_data.map.columns)]
			== 'S'))
	{
		g_player.rotation_angle = 90;
		return ;
	}
	else if ((g_game_data.map.map[j + (i * g_game_data.map.columns)]
			== 'E'))
	{
		g_player.rotation_angle = 0;
		return ;
	}
	else if ((g_game_data.map.map[j + (i * g_game_data.map.columns)]
			== 'W'))
	{
		g_player.rotation_angle = 180;
		return ;
	}
}
