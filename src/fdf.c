/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:07:08 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/12 04:47:37 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	my_mlx_pixel_put(t_img *data, float x, float y, int color)
{
	char	*dst;

	if (x <= LENGTH && x >= 0 && y <= HEIGHT && y >= 0)
	{
		dst = data->address + (int)(y * data->line_l + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

static void	print_map(t_args *args, t_map **start)
{
	t_3_vectors	point;
	t_2_vectors	coords;
	t_map		*map;
	int			i;

	map = *start;
	point.y = 0;
	while (map)
	{
		point.x = 0;
		i = 0;
		while (i < args->size_x)
		{
			point.z = map->row[i];
			coords.x = point.x + cosf(120) * point.z;
			coords.y = point.y + sinf(120) * point.z;
//			coords.x = point.x * cosf(120) + point.y * cosf(122) + point.z * cosf(118);
//			coords.y = point.x * sinf(120) + point.y * sinf(122) + point.z * sinf(118);
			my_mlx_pixel_put(args->img, coords.x, coords.y, 0x00FFFFFF);
			point.x += 1;
			++i;
		}
		point.y += 1;
		map = map->next;
	}
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
	args->vars->window = mlx_new_window(args->vars->mlx, LENGTH, HEIGHT,
			argv[1]);
	args->img->image = mlx_new_image(args->vars->mlx, LENGTH, HEIGHT);
	args->img->address = mlx_get_data_addr(args->img->image, &args->img->bpp,
			&args->img->line_l, &args->img->endian);
	print_map(args, &args->map);
	mlx_put_image_to_window(args->vars->mlx, args->vars->window,
		args->img->image, 0, 0);
	mlx_hook(args->vars->window, KEYDOWN, 1L << 0, key_switch, args);
	mlx_hook(args->vars->window, DESTROY, 1L << 0, close_window, args);
	mlx_loop(args->vars->mlx);
	exit_msg(args, NULL, 1, 0);
	// Free
	// mlx_loop_end(void *mlx_ptr)
}
