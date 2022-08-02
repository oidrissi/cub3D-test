/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-ghem <ael-ghem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 03:15:30 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/08/02 05:02:28 by ael-ghem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	h_ray_wall_check(void)
{
	t_data	*m;

	m = g();
	while (m->g_ray.h_ray_data.nexthorztouchy >= 0
		&& m->g_ray.h_ray_data.nexthorztouchy <= m->g_game_data.map.rows * T_S
		&& m->g_ray.h_ray_data.nexthorztouchx <= m->g_game_data.map.columns * T_S
		&& m->g_ray.h_ray_data.nexthorztouchx >= 0)
	{
		if (iswall(m->g_ray.h_ray_data.nexthorztouchx,
				m->g_ray.h_ray_data.nexthorztouchy))
		{
			(m->g_ray.h_ray_data.foundhorzwallhit = 1);
			m->g_ray.h_ray_data.horzwallhitx = m->g_ray.h_ray_data.nexthorztouchx;
			if (m->g_ray.rayup)
				m->g_ray.h_ray_data.horzwallhity
					= ++m->g_ray.h_ray_data.nexthorztouchy;
			else
				m->g_ray.h_ray_data.horzwallhity = m->g_ray.h_ray_data.nexthorztouchy;
			break ;
		}
		else
		{
			m->g_ray.h_ray_data.nexthorztouchx += m->g_ray.xstep;
			m->g_ray.h_ray_data.nexthorztouchy += m->g_ray.ystep;
		}
	}
	m->g_ray.h_ray_data.horzhitdistance = dis_2_points(m->g_player.x, m->g_player.y,
			m->g_ray.h_ray_data.horzwallhitx, m->g_ray.h_ray_data.horzwallhity);
}

void	h_ray(float angle)
{
	t_data	*m;

	m = g();
	m->g_ray.h_ray_data.foundhorzwallhit = 0;
	m->g_ray.h_ray_data.horzwallhitx = 0;
	m->g_ray.h_ray_data.horzwallhity = 0;
	m->g_ray.yhintercept = floor(m->g_player.y / T_S) * T_S;
	if (m->g_ray.raydown)
		m->g_ray.yhintercept += T_S;
	m->g_ray.xhintercept = m->g_player.x
		+ (m->g_ray.yhintercept - m->g_player.y) / tan(angle);
	m->g_ray.ystep = T_S;
	if (m->g_ray.rayup)
		m->g_ray.ystep *= -1;
	m->g_ray.xstep = T_S / tan(angle);
	if (m->g_ray.rayleft && m->g_ray.xstep > 0)
		m->g_ray.xstep *= -1;
	if (m->g_ray.rayright && m->g_ray.xstep < 0)
		m->g_ray.xstep *= -1;
	m->g_ray.h_ray_data.nexthorztouchy = m->g_ray.yhintercept;
	m->g_ray.h_ray_data.nexthorztouchx = m->g_ray.xhintercept;
	if (m->g_ray.rayup)
		m->g_ray.h_ray_data.nexthorztouchy--;
	h_ray_wall_check();
	if (!m->g_ray.h_ray_data.foundhorzwallhit)
		m->g_ray.h_ray_data.horzhitdistance = INT_MAX;
}

void	v_ray_wall_check(void)
{
	t_data	*m;

	m = g();
	while (m->g_ray.v_ray_data.nextverttouchy >= 0
		&& m->g_ray.v_ray_data.nextverttouchy <= m->g_game_data.map.rows * T_S
		&& m->g_ray.v_ray_data.nextverttouchx <= m->g_game_data.map.columns * T_S
		&& m->g_ray.v_ray_data.nextverttouchx >= 0)
	{
		if (iswall(m->g_ray.v_ray_data.nextverttouchx,
				m->g_ray.v_ray_data.nextverttouchy))
		{
			left_wall_check();
			break ;
		}
		else
		{
			m->g_ray.v_ray_data.nextverttouchx += m->g_ray.xstep;
			m->g_ray.v_ray_data.nextverttouchy += m->g_ray.ystep;
		}
	}
	m->g_ray.v_ray_data.verthitdistance = dis_2_points(m->g_player.x, m->g_player.y,
			m->g_ray.v_ray_data.vertwallhitx, m->g_ray.v_ray_data.vertwallhity);
}

void	v_ray(float angle)
{
	t_data	*m;

	m = g();
	m->g_ray.v_ray_data.foundvertwallhit = 0;
	m->g_ray.v_ray_data.vertwallhitx = 0;
	m->g_ray.v_ray_data.vertwallhity = 0;
	m->g_ray.xvintercept = floor(m->g_player.x / T_S) * T_S;
	if (m->g_ray.rayright)
		m->g_ray.xvintercept += T_S;
	m->g_ray.yvintercept = m->g_player.y
		+ (m->g_ray.xvintercept - m->g_player.x) * tan(angle);
	m->g_ray.xstep = T_S;
	if (m->g_ray.rayleft)
		m->g_ray.xstep *= -1;
	m->g_ray.ystep = T_S * tan(angle);
	if (m->g_ray.rayup && m->g_ray.ystep > 0)
		m->g_ray.ystep *= -1;
	if (m->g_ray.raydown && m->g_ray.ystep < 0)
		m->g_ray.ystep *= -1;
	m->g_ray.v_ray_data.nextverttouchy = m->g_ray.yvintercept;
	m->g_ray.v_ray_data.nextverttouchx = m->g_ray.xvintercept;
	if (m->g_ray.rayleft)
		m->g_ray.v_ray_data.nextverttouchx--;
	v_ray_wall_check();
	if (!m->g_ray.v_ray_data.foundvertwallhit)
		m->g_ray.v_ray_data.verthitdistance = INT_MAX;
}

void	cast_ray(float angle)
{
	t_data	*m;

	m = g();
	angle = normalise_angle(angle);
	initializer();
	m->g_ray.raydown = (angle > 0 && angle < 180);
	m->g_ray.rayup = !m->g_ray.raydown;
	m->g_ray.rayleft = (angle > 90 && angle < 270);
	m->g_ray.rayright = !m->g_ray.rayleft;
	h_ray(RAD_ANGLE(angle));
	v_ray(RAD_ANGLE(angle));
	if (m->g_ray.v_ray_data.verthitdistance
		> m->g_ray.h_ray_data.horzhitdistance)
		m->g_ray.distance = m->g_ray.h_ray_data.horzhitdistance;
	else
		m->g_ray.distance = m->g_ray.v_ray_data.verthitdistance;
	m->g_ray.washitvertical = (m->g_ray.v_ray_data.verthitdistance
			< m->g_ray.h_ray_data.horzhitdistance);
	if (m->g_ray.v_ray_data.verthitdistance
		> m->g_ray.h_ray_data.horzhitdistance)
		m->g_ray.wallhitx = m->g_ray.h_ray_data.horzwallhitx;
	else
		m->g_ray.wallhitx = m->g_ray.v_ray_data.vertwallhitx;
	if (m->g_ray.v_ray_data.verthitdistance
		> m->g_ray.h_ray_data.horzhitdistance)
		m->g_ray.wallhity = m->g_ray.h_ray_data.horzwallhity;
	else
		m->g_ray.wallhity = m->g_ray.v_ray_data.vertwallhity;
}
