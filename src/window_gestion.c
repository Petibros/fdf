/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:01:36 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/18 10:28:52 by sacgarci         ###   ########.fr       */
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
	if (keycode == 65362 || keycode == 4)
		args->scale += 0.005 + fabsf(args->scale / 10);
	else
		args->scale -= 0.005 + fabsf(args->scale / 10);
}

int	close_window(t_args *args)
{
	mlx_destroy_window(args->vars->mlx, args->vars->window);
	mlx_destroy_image(args->vars->mlx, args->img->image);
	exit_msg(args, NULL, 1, 0);
	return (0);
}

int	mouse_reset(int x, int y, t_args *args)
{
	args->last_pos.x = x;
	args->last_pos.y = y;
	return (0);
}

int	mouse_translation(int x, int y, t_args *args)
{
	args->start_x += x - args->last_pos.x;
	args->start_y += y - args->last_pos.y;
	mouse_reset(x, y, args);
	printf("%d;%d\n", x, y);
	return (0);
}

int	mouse_gestion(int button, int x, int y, t_args *args)
{
	if (button == 4 || button == 5)
		zoom(args, button);
	else if (button == 3)
		mouse_reset(x, y, args);
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
	printf("%d \n", keycode);
	printf("%f %f %f\n", args->rotates.y, args->rotates.z, args->rotates.x);
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
