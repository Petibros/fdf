/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:01:36 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/23 22:07:23 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	translation(t_args *args, int keycode)
{
	int	to_add;

	to_add = args->scale / (args->scale / 10);
	if (keycode == 119)
		args->start_y -= to_add;
	else if (keycode == 97)
		args->start_x -= to_add;
	else if (keycode == 115)
		args->start_y += to_add;
	else
		args->start_x += to_add;
}

static void	zoom(t_args *args, int keycode)
{
	float		scale_factor;
	t_2_vectors	vector;

	vector.x = args->last_pos.x - args->start_x; 
	vector.y = args->last_pos.y - args->start_y; 
	scale_factor = 1.1;

	if (keycode == 65362 || keycode == 4)
	{
		args->scale *= scale_factor;
		args->button = 4;
		args->start_x += (vector.x - vector.x * scale_factor);
		args->start_y += (vector.y - vector.y * scale_factor);
	}
	else
	{
		args->scale /= scale_factor;
		args->button = 5;
		args->start_x -= (vector.x - vector.x * scale_factor);
		args->start_y -= (vector.y - vector.y * scale_factor);
	}
	printf("%d %d %f\n", args->start_x, args->start_y, scale_factor);
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

int	mouse_reset(int x, int y, t_args *args)
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
	if (args->button == 3)
	{
		args->start_x += (x - args->last_pos.x) / (args->size_x / args->size_y);
		args->start_y += y - args->last_pos.y;
	}
	else if (args->button == 1)
	{
		args->rotates.x -= y - args->last_pos.y;
		args->rotates.y -= x - args->last_pos.x;
	}
	mouse_reset(x, y, args);
	return (0);
}

int	mouse_gestion(int button, int x, int y, t_args *args)
{
	if (button == 4 || button == 5)
	{
		mouse_reset(x, y, args);
		zoom(args, button);
	}
	if (button == 3 || button == 1)
		mouse_reset(x, y, args);
	if (button == 2)
	{
		center_map(args);
		args->button = 2;
	}
	else if (button == 1)
		args->button = 1;
	else if (button == 3)
		args->button = 3;
	printf("%d;%d   %d\n", x, y, button);
	return (0);
}

int	key_switch(int keycode, t_args *args)
{
	if (keycode == 65307)
		close_window(args);
	else if (keycode == 65362 || keycode == 65364)
		zoom(args, keycode);
	else if (keycode == 65361 || keycode == 65363)
		change_height(args, keycode);
	else if (keycode == 119 || keycode == 100 || keycode == 115
		|| keycode == 97)
		translation(args, keycode);
	else if (keycode == 65432 || keycode == 65429 || keycode == 65430
		|| keycode == 65431 || keycode == 65437 || keycode == 65434)
		get_rotates(args, keycode);
	else if (keycode == 32)
	{
		if (args->f == &draw_curv)
			args->f = &draw_iso;
		else
			args->f = &draw_curv;
	}
	return (0);
}

int	render_frame(t_args *args)
{
	reset_image(args->img);
	print_map(args);
	mlx_put_image_to_window(args->vars->mlx, args->vars->window,
		args->img->image, 0, 0);
	return (0);
}
