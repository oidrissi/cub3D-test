/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 03:36:02 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/07/30 20:56:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_atoi(const char *ptr)
{
	long	res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while ((ptr[i] >= 9 && ptr[i] <= 13) || ptr[i] == ' ')
		i++;
	if (ptr[i] == '+' || ptr[i] == '-')
	{
		if (ptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ptr[i] && ptr[i] >= '0' && ptr[i] <= '9')
	{
		res = res * 10 + (ptr[i] - '0');
		i++;
	}
	return (res * sign);
}

long long	ft_atoi2(const char *ptr)
{
	long long	res;
	int			sign;
	int			i;

	res = 0;
	sign = 1;
	i = 0;
	while ((ptr[i] >= 9 && ptr[i] <= 13) || ptr[i] == ' ')
		i++;
	if (ptr[i] == '+' || ptr[i] == '-')
	{
		if (ptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ptr[i] && ptr[i] >= '0' && ptr[i] <= '9')
	{
		res = res * 10 + (ptr[i] - '0');
		i++;
	}
	return (res * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!size)
		return (ft_strlen(src));
	while (src[i] && i + 1 < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

void	left_wall_check(void)
{
	g_ray.v_ray_data.foundvertwallhit = 1;
	if (g_ray.rayleft)
		g_ray.v_ray_data.vertwallhitx
			= ++g_ray.v_ray_data.nextverttouchx;
	else
		g_ray.v_ray_data.vertwallhitx = g_ray.v_ray_data.nextverttouchx;
	g_ray.v_ray_data.vertwallhity
		= g_ray.v_ray_data.nextverttouchy;
}
