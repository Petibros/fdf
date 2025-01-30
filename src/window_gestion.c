/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:01:36 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/28 18:10:50 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	center_map(t_args *args)
{
	float	dx;
	float	dy;

	dx = ((args->size_x / 2) - (args->size_y / 2)) * args->cos_val;
	dy = ((args->size_x / 2) + (args->size_y / 2)) * args->sin_val;
	args->start_x = (LENGTH / 2) - dx * args->scale;
	args->start_y = (HEIGHT / 2) - dy * args->scale;
}

int	close_window(t_args *args)
{
	mlx_destroy_window(args->vars->mlx, args->vars->window);
	mlx_destroy_image(args->vars->mlx, args->img->image);
	mlx_destroy_display(args->vars->mlx);
	free(args->vars->mlx);
	exit_msg(args, NULL, 1, 0);
	return (0);
}

int	key_switch(int keycode, t_args *args)
{
	if (keycode == ESC)
		close_window(args);
	return (0);
}
