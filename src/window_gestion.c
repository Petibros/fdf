/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:01:36 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/17 06:24:23 by sacgarci         ###   ########.fr       */
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
	if (keycode == 65362)
		args->scale += 0.005 + fabsf(args->scale / 50);
	else
		args->scale -= 0.005 + fabsf(args->scale / 50);
}

int	close_window(t_args *args)
{
	mlx_destroy_window(args->vars->mlx, args->vars->window);
	mlx_destroy_image(args->vars->mlx, args->img->image);
	exit_msg(args, NULL, 1, 0);
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
	else if (keycode == 119 || keycode == 100
		|| keycode == 115 || keycode == 97)
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
