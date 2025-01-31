/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:07:08 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/28 16:23:32 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	close_window(t_args *args)
{
	mlx_destroy_window(args->vars->mlx, args->vars->window);
	mlx_destroy_image(args->vars->mlx, args->img->image);
	mlx_destroy_display(args->vars->mlx);
	free(args->vars->mlx);
	exit_msg(args, NULL, 1, 0);
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

static void	init_args(t_args *args)
{
	args->vars = malloc(sizeof(t_vars));
	if (!args->vars)
		exit_msg(args, "Failed to alloc vars", 1, 1);
	args->img = malloc(sizeof(t_img));
	if (!args->img)
		exit_msg(args, "Failed to alloc img", 1, 1);
	args->vars->mlx = mlx_init();
	args->scale = (LENGTH / 5 * 3) / fabs((sqrt((pow(args->size_x, 2)
						+ pow(args->size_y, 2)))
				- (args->lowest - args->highest)));
	args->height = 1;
	args->diff = fmaxf(fabs(args->highest), fabs(args->lowest));
	if (!args->diff)
		args->diff = 1;
	args->rotates.x = 0;
	args->rotates.y = 0;
	args->f = &draw_iso;
	args->button = 0;
	get_colors(args);
	center_map(args);
}

static void	fdf(t_args *args, char **argv)
{
	args->vars->window = mlx_new_window
		(args->vars->mlx, LENGTH, HEIGHT, argv[1]);
	args->img->image = mlx_new_image(args->vars->mlx, LENGTH, HEIGHT);
	args->img->address = mlx_get_data_addr(args->img->image, &args->img->bpp,
			&args->img->line_l, &args->img->endian);
	print_map(args);
	mlx_put_image_to_window(args->vars->mlx, args->vars->window,
		args->img->image, 0, 0);
	mlx_hook(args->vars->window, KEYDOWN, 1L << 0, key_switch, args);
	mlx_hook(args->vars->window, DESTROY, 1L << 0, close_window, args);
	mlx_hook(args->vars->window, MOUSE_MOVE, 1L << 13, mouse_movement, args);
	mlx_mouse_hook(args->vars->window, mouse_gestion, args);
	mlx_loop_hook(args->vars->mlx, render_frame, args);
	mlx_loop(args->vars->mlx);
}

int	main(int argc, char **argv)
{
	t_args	*args;

	if (argc != 2)
		exit_miss_args();
	args = malloc(sizeof(t_args));
	if (!args)
		exit_msg(args, "Failed to alloc args", 0, 1);
	args->colors = malloc(sizeof(t_colors));
	if (!args->colors)
		exit_msg(args, "Failed to alloc colors", 0, 1);
	args->colors->i = 0;
	args->colors->tab_size = 7;
	parsing(argv, args);
	init_args(args);
	fdf(args, argv);
}
