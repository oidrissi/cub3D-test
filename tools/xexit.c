/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xexit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:41:53 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/08/02 03:45:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*ftft(void)
{
	void	*tmp;

	tmp = g_rtn;
	g_rtn = NULL;
	return (tmp);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}


void	*xexit(int x)
{
	xflush();
	exit(x);
	return ((void *)0);
}
