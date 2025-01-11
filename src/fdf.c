/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:07:08 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/11 02:51:54 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->address + (y * data->line_l + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

static void	print_map(int y, int x, t_args *args, t_map **start)
{
	int	n_length = 0;
	int	i;
	int	n_width = 0;
	t_map	*map;

	map = *start;
	while (map)
	{
		n_length = 0;
		i = 0;
		while (n_length < args->size_x)
		{
			my_mlx_pixel_put(args->img, x + i, y + n_width, 0xFF00FFFF + map->row[n_length] * 20);
			if (i != 0 && i % (1920 / args->size_x) == 0)
				++n_length;
			++i;
		}
		++n_width;
		if (n_width != 0 && n_width % (1080 / args->size_y) == 0)
			map = map->next;
	}
}

int	close_win(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		mlx_destroy_window(vars->mlx, vars->window);
	return (keycode);
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
}

int	main(int argc, char **argv)
{
	t_args	*args;
	
	if (argc != 2)
		exit_miss_args();
	args = parsing(argv);
	init_args(args);
	args->vars->window = mlx_new_window(args->vars->mlx, 1920, 1080, argv[1]);
	args->img->image = mlx_new_image(args->vars->mlx, 1920, 1080);
	args->img->address = mlx_get_data_addr(args->img->image, &args->img->bpp,
						&args->img->line_l, &args->img->endian);
	print_map(0, 0, args, &args->map);
	mlx_put_image_to_window(args->vars->mlx, args->vars->window,
						args->img->image, 0, 0);
	mlx_hook(args->vars->window, 2, 1L<<0, close_win, args->vars);
	mlx_loop(args->vars->mlx);
	exit_msg(args, NULL, 1, 0);
}
