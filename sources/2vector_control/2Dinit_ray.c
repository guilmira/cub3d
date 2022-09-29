/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2Dinit_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:14:55 by guilmira          #+#    #+#             */
/*   Updated: 2022/09/29 20:36:10 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/** PURPOSE : Get distance at the beginnig of the coordinate. */
void	get_relative_distance(t_ray *ray, t_prog *game)
{
	ray->relative_distance[0] = 0;
	ray->relative_distance[1] = 0;
	ray->relative_distance[0] = ray->origin[0] - \
	(double) ray->pos[0] * game->map2D.pixel_per_block[0];
	ray->relative_distance[1] = ray->origin[1] - \
	(double) ray->pos[1] * game->map2D.pixel_per_block[1];
}

/** PURPOSE : fix net distance.
 * 1. There is a difference between what 2D block 
 * we are at, and the exact coor location.
 *	Factor corrects that offset. */
static void	fix_net_distance(t_ray *ray, int case_factor, int block[])
{
	double	factor;

	if (case_factor == 1)
	{
		factor = (((double) ray->pos[0] + 1) * block[0] \
		- ray->origin[0]) / block[0];
		ray->net_distance[0] = (factor) * ray->delta[0];
	}
	else if (case_factor == 2)
	{
		factor = (ray->origin[0] - (double) ray->pos[0] * block[0]) / block[0];
		ray->net_distance[0] = (factor) * ray->delta[0];
	}
	else if (case_factor == 3)
	{
		factor = (((double) ray->pos[1] + 1) * block[1] \
		- ray->origin[1]) / block[1];
		ray->net_distance[1] = (factor) * ray->delta[1];
	}
	else if (case_factor == 4)
	{
		factor = (ray->origin[1] - (double) ray->pos[1] * block[1]) / block[1];
		ray->net_distance[1] = (factor) * ray->delta[1];
	}
}

/** PURPOSE : Init distance of delta x or delta y at first block.
 * 1. There is a difference between what 2D block 
 * we are at, and the exact coor location.
 *	Factor corrects that offset. */
static inline void	init_net_distance(t_ray *ray, \
t_vector direction, t_prog *game)
{
	ray->step[0] = ray->pos[0];
	ray->step[1] = ray->pos[1];
	get_relative_distance(ray, game);
	ray->step_increase[0] = 1;
	ray->step_increase[1] = 1;
	if (direction.x < 0)
		ray->step_increase[0] = -1;
	if (direction.y < 0)
		ray->step_increase[1] = -1;
	if (direction.x >= 0)
		fix_net_distance(ray, 1, game->map2D.pixel_per_block);
	else
		fix_net_distance(ray, 2, game->map2D.pixel_per_block);
	if (direction.y >= 0)
		fix_net_distance(ray, 3, game->map2D.pixel_per_block);
	else
		fix_net_distance(ray, 4, game->map2D.pixel_per_block);
}

/** PURPOSE : Get coordinates of array. */
static inline void	update_location_map(t_ray *ray, \
double position[], int pixel_per_block[])
{
	ray->pos[0] = position[0] / pixel_per_block[0];
	ray->pos[1] = position[1] / pixel_per_block[1];
}

/** PURPOSE : Get the distance of OX between 2 
 * vertical lines that represent a wall.
 * Or the equivalent of OY. */
static inline void	get_delta(t_ray *ray, t_vector dir)
{
	if (dir.x)
		ray->delta[0] = fabs(1 / dir.x);
	if (dir.y)
		ray->delta[1] = fabs(1 / dir.y);
}

/** PURPOSE : Init values
 * 1. Delta is the distance of OX between 2 vertical 
 * lines that represent a wall. */
void	init_ray(t_ray *ray, double origin[], t_vector dir, t_prog *game)
{
	ray->origin[0] = origin[0];
	ray->origin[1] = origin[1];
	ray->dir = dir;
	ray->resultant_vector.x = 0;
	ray->resultant_vector.y = 0;
	update_location_map(ray, origin, game->map2D.pixel_per_block);
	ray->delta[0] = 0;
	ray->delta[1] = 0;
	ray->face = 0;
	get_delta(ray, ray->dir);
	init_net_distance(ray, ray->dir, game);
}
