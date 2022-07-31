/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 03:15:30 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/07/30 20:56:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	h_ray_wall_check(void)
{
	while (g_ray.h_ray_data.nexthorztouchy >= 0
		&& g_ray.h_ray_data.nexthorztouchy <= g_game_data.map.rows * T_S
		&& g_ray.h_ray_data.nexthorztouchx <= g_game_data.map.columns * T_S
		&& g_ray.h_ray_data.nexthorztouchx >= 0)
	{
		if (iswall(g_ray.h_ray_data.nexthorztouchx,
				g_ray.h_ray_data.nexthorztouchy))
		{
			(g_ray.h_ray_data.foundhorzwallhit = 1);
			g_ray.h_ray_data.horzwallhitx
				= g_ray.h_ray_data.nexthorztouchx;
			if (g_ray.rayup)
				g_ray.h_ray_data.horzwallhity++;
			else
				g_ray.h_ray_data.horzwallhity = g_ray.h_ray_data.nexthorztouchy;
			break ;
		}
		else
		{
			g_ray.h_ray_data.nexthorztouchx += g_ray.xstep;
			g_ray.h_ray_data.nexthorztouchy += g_ray.ystep;
		}
	}
	g_ray.h_ray_data.horzhitdistance = dis_2_points(g_player.x, g_player.y,
			g_ray.h_ray_data.horzwallhitx, g_ray.h_ray_data.horzwallhity);
}

void	h_ray(float angle)
{
	g_ray.h_ray_data.foundhorzwallhit = 0;
	g_ray.h_ray_data.horzwallhitx = 0;
	g_ray.h_ray_data.horzwallhity = 0;
	g_ray.yhintercept = floor(g_player.y / T_S) * T_S;
	if (g_ray.raydown)
		g_ray.yhintercept += T_S;
	g_ray.xhintercept = g_player.x
		+ (g_ray.yhintercept - g_player.y) / tan(angle);
	g_ray.ystep = T_S;
	if (g_ray.rayup)
		g_ray.ystep *= -1;
	g_ray.xstep = T_S / tan(angle);
	if (g_ray.rayleft && g_ray.xstep > 0)
		g_ray.xstep *= -1;
	if (g_ray.rayright && g_ray.xstep < 0)
		g_ray.xstep *= -1;
	g_ray.h_ray_data.nexthorztouchy = g_ray.yhintercept;
	g_ray.h_ray_data.nexthorztouchx = g_ray.xhintercept;
	if (g_ray.rayup)
		g_ray.h_ray_data.nexthorztouchy--;
	h_ray_wall_check();
	if (!g_ray.h_ray_data.foundhorzwallhit)
		g_ray.h_ray_data.horzhitdistance = INT_MAX;
}

void	v_ray_wall_check(void)
{
	while (g_ray.v_ray_data.nextverttouchy >= 0
		&& g_ray.v_ray_data.nextverttouchy <= g_game_data.map.rows * T_S
		&& g_ray.v_ray_data.nextverttouchx <= g_game_data.map.columns * T_S
		&& g_ray.v_ray_data.nextverttouchx >= 0)
	{
		if (iswall(g_ray.v_ray_data.nextverttouchx,
				g_ray.v_ray_data.nextverttouchy))
		{
			left_wall_check();
			break ;
		}
		else
		{
			g_ray.v_ray_data.nextverttouchx += g_ray.xstep;
			g_ray.v_ray_data.nextverttouchy += g_ray.ystep;
		}
	}
	g_ray.v_ray_data.verthitdistance = dis_2_points(g_player.x, g_player.y,
			g_ray.v_ray_data.vertwallhitx, g_ray.v_ray_data.vertwallhity);
}

void	v_ray(float angle)
{
	g_ray.v_ray_data.foundvertwallhit = 0;
	g_ray.v_ray_data.vertwallhitx = 0;
	g_ray.v_ray_data.vertwallhity = 0;
	g_ray.xvintercept = floor(g_player.x / T_S) * T_S;
	if (g_ray.rayright)
		g_ray.xvintercept += T_S;
	g_ray.yvintercept = g_player.y
		+ (g_ray.xvintercept - g_player.x) * tan(angle);
	g_ray.xstep = T_S;
	if (g_ray.rayleft)
		g_ray.xstep *= -1;
	g_ray.ystep = T_S * tan(angle);
	if (g_ray.rayup && g_ray.ystep > 0)
		g_ray.ystep *= -1;
	if (g_ray.raydown && g_ray.ystep < 0)
		g_ray.ystep *= -1;
	g_ray.v_ray_data.nextverttouchy = g_ray.yvintercept;
	g_ray.v_ray_data.nextverttouchx = g_ray.xvintercept;
	if (g_ray.rayleft)
		g_ray.v_ray_data.nextverttouchx--;
	v_ray_wall_check();
	if (!g_ray.v_ray_data.foundvertwallhit)
		g_ray.v_ray_data.verthitdistance = INT_MAX;
}

void	cast_ray(float angle)
{
	angle = normalise_angle(angle);
	initializer();
	g_ray.raydown = (angle > 0 && angle < 180);
	g_ray.rayup = !g_ray.raydown;
	g_ray.rayleft = (angle > 90 && angle < 270);
	g_ray.rayright = !g_ray.rayleft;
	h_ray(RAD_ANGLE(angle));
	v_ray(RAD_ANGLE(angle));
	if (g_ray.v_ray_data.verthitdistance
		> g_ray.h_ray_data.horzhitdistance)
		g_ray.distance = g_ray.h_ray_data.horzhitdistance;
	else
		g_ray.distance = g_ray.v_ray_data.verthitdistance;
	g_ray.washitvertical = (g_ray.v_ray_data.verthitdistance
			< g_ray.h_ray_data.horzhitdistance);
	if (g_ray.v_ray_data.verthitdistance
		> g_ray.h_ray_data.horzhitdistance)
		g_ray.wallhitx = g_ray.h_ray_data.horzwallhitx;
	else
		g_ray.wallhitx = g_ray.v_ray_data.vertwallhitx;
	if (g_ray.v_ray_data.verthitdistance
		> g_ray.h_ray_data.horzhitdistance)
		g_ray.wallhity = g_ray.h_ray_data.horzwallhity;
	else
		g_ray.wallhity = g_ray.v_ray_data.vertwallhity;
}
