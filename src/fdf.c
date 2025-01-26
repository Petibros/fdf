/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:07:08 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/24 01:06:51 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_args(t_args *args)
{
	args->vars = malloc(sizeof(t_vars));
	if (!args->vars)
		exit_msg(args, "Failed to alloc vars", 1, 1);
	args->img = malloc(sizeof(t_img));
	if (!args->img)
		exit_msg(args, "Failed to alloc img", 1, 1);
	args->vars->mlx = mlx_init();
	args->scale = (LENGTH / 5 * 3) / fabs((sqrt((pow(args->size_x, 2) + pow(args->size_y, 2))) - (args->lowest - args->highest)));
	args->height = 1;
	args->rotates.x = 0;
	args->rotates.y = 0;
	args->f = &draw_iso;
	args->sin_val = sinf(30 * M_PI / 180);
	args->cos_val = cosf(30 * M_PI / 180);
	center_map(args);
}

int	main(int argc, char **argv)
{
	t_args	*args;

	if (argc != 2)
		exit_miss_args();
	args = parsing(argv);
	init_args(args);
	args->vars->window = mlx_new_window(args->vars->mlx, LENGTH, HEIGHT,
			argv[1]);
	args->img->image = mlx_new_image(args->vars->mlx, LENGTH, HEIGHT);
	args->img->address = mlx_get_data_addr(args->img->image, &args->img->bpp,
			&args->img->line_l, &args->img->endian);
	print_map(args);
	mlx_put_image_to_window(args->vars->mlx, args->vars->window,
		args->img->image, 0, 0);
	mlx_hook(args->vars->window, KEYDOWN, 1L << 0, key_switch, args);
	mlx_hook(args->vars->window, DESTROY, 1L << 0, close_window, args);
	mlx_hook(args->vars->window, 6, 1L << 13, mouse_movement, args);
	mlx_mouse_hook(args->vars->window, mouse_gestion, args);
	mlx_loop_hook(args->vars->mlx, render_frame, args);
	mlx_loop(args->vars->mlx);
	exit_msg(args, NULL, 1, 0);
}
