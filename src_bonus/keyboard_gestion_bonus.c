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

static void	change_height(t_args *args, int keycode)
{
	if (keycode == ARROW_R)
		args->height += fabsf((args->height / 50)) + 0.002;
	else
		args->height -= fabsf((args->height / 50)) + 0.002;
}

static void	get_rotates(t_args *args, int keycode)
{
	if (keycode == NUM_4)
		args->rotates.y -= 1;
	else if (keycode == NUM_7)
		args->rotates.y += 1;
	else if (keycode == NUM_6)
		args->rotates.x -= 1;
	else if (keycode == NUM_9)
		args->rotates.x += 1;
}

static void	translation(t_args *args, int keycode)
{
	int	to_add;

	to_add = args->scale / (args->scale / 10);
	if (keycode == W)
		args->start_y -= to_add;
	else if (keycode == A)
		args->start_x -= to_add;
	else if (keycode == S)
		args->start_y += to_add;
	else
		args->start_x += to_add;
}

static void	change_perspective(t_args *args)
{
	if (args->f == &draw_iso)
		args->f = &draw_curv;
	else if (args->f == &draw_curv)
		args->f = &draw_cava;
	else
		args->f = &draw_iso;
}

int	key_switch(int keycode, t_args *args)
{
	if (keycode == ESC)
		close_window(args);
	else if (keycode == ARROW_U || keycode == ARROW_D)
		zoom(args, keycode);
	else if (keycode == ARROW_R || keycode == ARROW_L)
		change_height(args, keycode);
	else if (keycode == W || keycode == A || keycode == S || keycode == D)
		translation(args, keycode);
	else if (keycode == NUM_7 || keycode == NUM_4
		|| keycode == NUM_9 || keycode == NUM_6)
		get_rotates(args, keycode);
	else if (keycode == SPACE)
		change_perspective(args);
	else if (keycode == C)
	{
		++args->colors->i;
		if (args->colors->i >= args->colors->tab_size)
			args->colors->i = 0;
	}
	return (0);
}
