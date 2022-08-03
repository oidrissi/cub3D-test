/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:06:30 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/08/03 15:37:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	destroy_window(void)
{
	mlx_destroy_image(g()->g_mlx_ptr, g()->g_img.img_ptr);
	mlx_destroy_window(g()->g_mlx_ptr, g()->g_win_ptr);
	byebye();
	return (0);
}

void	init_game(void)
{
	g()->g_num_rays = g()->g_game_data.res.width;
	g()->g_speed = g()->g_game_data.res.width \
	/ (g()->g_game_data.res.width / 12);
	g()->g_mlx_ptr = mlx_init();
	g()->g_img.img_ptr = mlx_new_image(g()->g_mlx_ptr, \
	g()->g_game_data.res.width, g()->g_game_data.res.height);
	g()->g_img.addr = (int *)mlx_get_data_addr(g()->g_img.img_ptr, \
	&g()->g_img.bpp, &g()->g_img.line_length, &g()->g_img.endian);
}

int	main(int ac, char **av)
{
	if (ac < 2 && write(2, "No .cub file entered\n", 21))
		exit(0);
	if (ac > 3 && write(2, "Too many arguments!\n", 20))
		exit(0);
	if (set_route(read_input(av[1])) == -1
		&& write(2, "Configuration file error\n", 25))
		byebye();
	check_args(ac, av);
	mlx_hook(g()->g_win_ptr, 2, 1L << 0, key_pressed, (void *)0);
	mlx_hook(g()->g_win_ptr, 3, 1L << 1, key_released, (void *)0);
	mlx_hook(g()->g_win_ptr, 17, 0L, destroy_window, (void *)0);
	mlx_loop_hook(g()->g_mlx_ptr, render_frames, (void *)0);
	mlx_loop(g()->g_mlx_ptr);
	return (0);
}
