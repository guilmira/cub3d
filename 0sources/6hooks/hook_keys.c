/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 10:32:07 by guilmira          #+#    #+#             */
/*   Updated: 2022/08/20 12:23:31 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/** PURPOSE : Correct minimap status and reset screen. */
void	update_player_location(t_prog *game)
{
	int coor_x;
	int coor_y;
	int count;

	coor_x = game->pl.position[0];
	coor_y = game->pl.position[1];
	count = 1;
	while (42)
	{
		if (game->map2D.layout[coor_y][coor_x] == 0)
			break ;
		else if (game->map2D.layout[coor_y][coor_x - count] == 0)
			coor_x -= count;
		else if (game->map2D.layout[coor_y][coor_x + count] == 0)
			coor_x += count;
		else if (game->map2D.layout[coor_y - count][coor_x] == 0)
			coor_y -= count;
		else if (game->map2D.layout[coor_y + count][coor_x] == 0)
			coor_y += count;
		count++;
	}
	game->pl.position_coor[0] = (double)(/*game->pl.position[0]*/coor_x) * 
	game->map2D.pixel_per_block[0] + (game->map2D.pixel_per_block[0] / 2);
	game->pl.position_coor[1] = (double)(game->map2D.map_y - (/*game->pl.position[1]*/coor_y)) * \
	game->map2D.pixel_per_block[1] + (game->map2D.pixel_per_block[1] / 2) - 1;
}

/** PURPOSE : Is there os is there not a minimap. */
static int	is_minimap(t_prog *game)
{
	if (!game->minimap_state)
		return (0);
	else if (game->minimap_state == 2 || game->minimap_state == 4)
		return (1);
	else
		return (0);
}

/** PURPOSE : Correct minimap status and reset screen. */
static void	correct_minimap_value(t_prog *game)
{
	game->minimap_state++;
	if (game->minimap_state == 6)
		game->minimap_state = 0;
}

/** PURPOSE : Executed when hitting tab. It executes twice */
static void	hook_control_minimap(t_prog *game)
{
	correct_minimap_value(game);
	if (is_minimap(game))
	{
		game->pl.flag_movement = 1;
		minimap_dimensions(game);
		update_pixel_per_block(game);
		update_player_location(game);
	}
}

/** PURPOSE : manage keys. */
void	hk_keys(mlx_key_data_t key, void *g)
{
	t_prog	*game;

	game = (t_prog *)g;
	if (key.key == MLX_KEY_ESCAPE)
		clean_exit(game);
	else if (key.key == MLX_KEY_TAB) //PACE por alguna razon las teclas se pulsan dos veces
		hook_control_minimap(game);
	else if (key.key == MLX_KEY_F)
	{
		ft_putstr_fd("Wind mode activated. Speed boosted.\n", 1);
		game->pl.flag_trance++;
	}
	else if (key.key == MLX_KEY_G)
	{
		if (game->pl.flag_trance)
		{
			ft_putstr_fd("Exhausted. Speed back to normal.\n", 1);
			game->pl.flag_trance--;
		}
	}
	else
		movement_control(key, game);
	vison_control(key, game);
}
