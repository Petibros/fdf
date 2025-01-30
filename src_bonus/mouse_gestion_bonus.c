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

#include "fdf_bonus.h"

void	zoom(t_args *args, int keycode)
{
	float		scale_factor;
	t_2_vectors	vector;

	vector.x = args->last_pos.x - args->start_x;
	vector.y = args->last_pos.y - args->start_y;
	scale_factor = 1.1;
	if (keycode == ARROW_U || keycode == SCROLL_U)
	{
		args->scale *= scale_factor;
		args->button = SCROLL_U;
		args->start_x += (vector.x - vector.x * scale_factor);
		args->start_y += (vector.y - vector.y * scale_factor);
	}
	else
	{
		args->scale /= scale_factor;
		args->button = SCROLL_D;
		args->start_x -= (vector.x - vector.x * scale_factor);
		args->start_y -= (vector.y - vector.y * scale_factor);
	}
}

static int	mouse_reset(int x, int y, t_args *args)
{
	args->last_pos.x = x;
	args->last_pos.y = y;
	return (0);
}

void	center_map(t_args *args)
{
	float	dx;
	float	dy;

	dx = ((args->size_x / 2) - (args->size_y / 2)) * args->cos_val;
	dy = ((args->size_x / 2) + (args->size_y / 2)) * args->sin_val;
	args->start_x = (LENGTH / 2) - dx * args->scale;
	args->start_y = (HEIGHT / 2) - dy * args->scale;
}

int	mouse_movement(int x, int y, t_args *args)
{
	if (args->button == MOUSE_R)
	{
		args->start_x += (x - args->last_pos.x) / (args->size_x / args->size_y);
		args->start_y += y - args->last_pos.y;
	}
	else if (args->button == MOUSE_L)
	{
		args->rotates.x -= y - args->last_pos.y;
		args->rotates.y -= x - args->last_pos.x;
	}
	mouse_reset(x, y, args);
	return (0);
}

int	mouse_gestion(int button, int x, int y, t_args *args)
{
	if (button == SCROLL_U || button == SCROLL_D)
	{
		mouse_reset(x, y, args);
		zoom(args, button);
	}
	if (button == MOUSE_R || button == MOUSE_L)
		mouse_reset(x, y, args);
	if (button == MOUSE_M)
	{
		center_map(args);
		args->button = MOUSE_M;
	}
	else if (button == MOUSE_L)
		args->button = MOUSE_L;
	else if (button == MOUSE_R)
		args->button = MOUSE_R;
	return (0);
}
