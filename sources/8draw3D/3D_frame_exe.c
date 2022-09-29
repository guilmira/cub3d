/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_frame_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:48:19 by guilmira          #+#    #+#             */
/*   Updated: 2022/09/29 17:21:00 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/** PURPOSE : raise 3D from raycast results.
 * 1. Draw first layer of the 3D: floor and horizon sky.
 * 2. Draw walls depending on ray distance collison. */
void	put_frame_three_dim(t_prog *game)
{
	//draw_gameplay_aid(game);
	draw_first_layer(game);
	draw_three_dimension_walls(game);
	//draw_player_left_hud(game);
}
