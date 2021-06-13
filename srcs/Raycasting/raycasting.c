/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:19:42 by bmangin           #+#    #+#             */
/*   Updated: 2021/06/08 14:44:70y bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray_side_and_step(t_ray *ray)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (ray->posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - ray->posX) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (ray->posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - ray->posY) * ray->deltaDistY;
	}
}

static void	init_ray(t_ray *ray, int w, int x)
{
	ray->cameraX = 2 * x / (float)(w) - 1;
	ray->rayDirX = ray->dirX + ray->planeX * ray->cameraX;
	ray->rayDirY = ray->dirY + ray->planeY * ray->cameraX;
	ray->mapX = (int)(ray->posX);
	ray->mapY = (int)(ray->posY);
	if (ray->rayDirY == 0)
		ray->deltaDistX = 0;
	else if (ray->rayDirX == 0)
		ray->deltaDistX = 1;
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX);
	if (ray->rayDirX == 0)
		ray->deltaDistY = 0;
	else if (ray->rayDirY == 0)
		ray->deltaDistY = 1;
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY);
	ray->hit = 0;
	init_ray_side_and_step(ray);
}

float	ft_dda(t_g *g, int x_win)
{
	init_ray(&g->ray, g->win.w, x_win);
	while (g->ray.hit == 0)
	{
		if (g->ray.sideDistX < g->ray.sideDistY)
			ft_dda_x_inf_y(&g->ray);
		else
			ft_dda_x_sup_y(&g->ray);
		if (g->map.map[g->ray.mapY][g->ray.mapX] == '1')
			g->ray.hit = 1;
		// if (g->map.map[g->ray.mapY][g->ray.mapX] == '2')
		// {
		// 	if (g->lst_sprite == NULL)
		// 		g->lst_sprite = ft_lst_new(g->ray.mapX + 0.5, g->ray.mapY + 0.5,
		// 				g->map.map[g->ray.mapY][g->ray.mapX] - '0');
		// 	else if (ft_in_lst(g->lst_sprite, g->ray.mapX + 0.5,
		// 			g->ray.mapY + 0.5) == 0)
		// 		ft_lstadd_frt(&g->lst_sprite, ft_lst_new(g->ray.mapX + 0.5,
		// 				g->ray.mapY + 0.5,
		// 				g->map.map[g->ray.mapY][g->ray.mapX] - '0'));
		// }
	}
	if (g->ray.side == 0)
		g->ray.perpWallDist = (g->ray.mapX - g->ray.posX + (1 - g->ray.stepX) / 2) / g->ray.rayDirX;
	else
		g->ray.perpWallDist = (g->ray.mapY - g->ray.posY + (1 - g->ray.stepY) / 2) / g->ray.rayDirY;
	g->zbuffer[x_win] = g->ray.perpWallDist;
	return (g->ray.perpWallDist);
	// return (ft_dist(&g->ray));
}
