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

#include "fdf.h"

static void	init_args(t_args *args)
{
	args->vars = malloc(sizeof(t_vars));
	if (!args->vars)
		exit_msg(args, "Failed to alloc vars", 6, 1);
	args->img = malloc(sizeof(t_img));
	if (!args->img)
		exit_msg(args, "Failed to alloc img", 7, 1);
	args->vars->mlx = mlx_init();
	if (!args->vars->mlx)
		exit_msg(args, "Problem with the display", 8, 1);
	args->scale = (LENGTH / 5 * 3) / fabs((sqrt((pow(args->size_x, 2)
						+ pow(args->size_y, 2)))
				- (args->lowest - args->highest)));
	args->sin_val = sinf(30 * M_PI / 180);
	args->cos_val = cosf(30 * M_PI / 180);
	center_map(args);
}

static void	fdf(t_args *args, char **argv)
{
	args->vars->window = mlx_new_window
		(args->vars->mlx, LENGTH, HEIGHT, argv[1]);
	if (!args->vars->window)
		exit_msg(args, "Problem with the window", 9, 1);
	args->img->image = mlx_new_image(args->vars->mlx, LENGTH, HEIGHT);
	if (!args->img->image)
		exit_msg(args, "Problem with the image", 10, 1);
	args->img->address = mlx_get_data_addr(args->img->image, &args->img->bpp,
			&args->img->line_l, &args->img->endian);
	if (!args->img->address)
	{
		close_window(args);
		perror("Problem getting the image's address");
	}
	print_map(args);
	mlx_put_image_to_window(args->vars->mlx, args->vars->window,
		args->img->image, 0, 0);
	mlx_hook(args->vars->window, KEYDOWN, 1L << 0, key_switch, args);
	mlx_hook(args->vars->window, DESTROY, 1L << 0, close_window, args);
	mlx_loop(args->vars->mlx);
}

int	main(int argc, char **argv)
{
	t_args	*args;

	if (argc != 2)
		exit_miss_args();
	args = malloc(sizeof(t_args));
	if (!args)
	{
		perror("Failed to alloc args");
		return (1);
	}
	parsing(argv, args);
	init_args(args);
	fdf(args, argv);
}
