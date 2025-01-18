/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:40:34 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/18 09:22:57 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	reset_image(t_img *image)
{
	t_2_vectors	coords;

	coords.y = 0;
	while (coords.y < HEIGHT)
	{
		coords.x = 0;
		while (coords.x < LENGTH)
		{
			my_mlx_pixel_put(image, coords.x, coords.y, 0x00000000);
			coords.x += 1;
		}
		coords.y += 1;
	}
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x <= LENGTH && x >= 0 && y <= HEIGHT && y >= 0)
	{
		dst = data->address + (int)(y * data->line_l + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_line(t_args *args, t_2_vectors coords_1, t_2_vectors coords_2)
{
	int			n;
	t_2_vectors	diff;
	int			i;

	i = 0;
	diff.x = coords_2.x - coords_1.x;
	diff.y = coords_2.y - coords_1.y;
	if (fabsf(diff.x) >= fabsf(diff.y))
		n = fabsf(diff.x);
	else
		n = fabsf(diff.y);
	diff.x = diff.x / n;
	diff.y = diff.y / n;
	while (i <= n)
	{
		my_mlx_pixel_put(args->img,
			(int)coords_1.x, (int)coords_1.y, 0xFFFFFFFF);
		coords_1.x += diff.x;
		coords_1.y += diff.y;
		++i;
	}
}

static void	draw_x_axis(t_args *args, t_3_vectors points, t_3_vectors next)
{
	t_2_vectors	coords_1;
	t_2_vectors	coords_2;

	coords_1.x = ((points.x * cosf((30 * M_PI) / 180) - points.y
				* cosf((30 * M_PI) / 180)) * args->scale) + args->start_x;
	coords_1.y = (points.x * sinf((30 * M_PI) / 180)
			+ points.y * sinf((30 * M_PI) / 180)) - (points.z * args->height);
	coords_1.y = coords_1.y * args->scale + args->start_y;
	coords_2.x = ((next.x * cosf((30 * M_PI) / 180) - next.y
				* cosf((30 * M_PI) / 180)) * args->scale) + args->start_x;
	coords_2.y = (next.x * sinf((30 * M_PI) / 180) + next.y
			* sinf((30 * M_PI) / 180)) - (next.z * args->height);
	coords_2.y = coords_2.y * args->scale + args->start_y;
	draw_line(args, coords_1, coords_2);
}

static void	draw_y_axis(t_args *args, t_3_vectors points, t_3_vectors next)
{
	t_2_vectors	coords_1;
	t_2_vectors	coords_2;

	coords_1.x = ((points.x * cosf((30 * M_PI) / 180) - points.y
				* cosf((30 * M_PI) / 180)) * args->scale) + args->start_x;
	coords_1.y = (points.x * sinf((30 * M_PI) / 180)
			+ points.y * sinf((30 * M_PI) / 180)) - (points.z * args->height);
	coords_1.y = coords_1.y * args->scale + args->start_y;
	coords_2.x = ((next.x * cosf((30 * M_PI) / 180) - next.y
				* cosf((30 * M_PI) / 180)) * args->scale) + args->start_x;
	coords_2.y = (next.x * sinf((30 * M_PI) / 180) + next.y
			* sinf((30 * M_PI) / 180)) - (next.z * args->height);
	coords_2.y = coords_2.y * args->scale + args->start_y;
	draw_line(args, coords_1, coords_2);
}

void	print_map(t_args *args)
{
	t_3_vectors	point;
	t_3_vectors	next;
	t_2_vectors	center;

	center.x = args->size_x / 2;
	center.y = args->size_y / 2;
	point.y = 0;
	while (point.y < args->size_y)
	{
		point.x = 0;
		while (point.x < args->size_x)
		{
			point.z = args->map[(int)point.y][(int)point.x];
			if (point.x + 1 < args->size_x)
			{
				next.z = args->map[(int)point.y][(int)point.x + 1];
				next.y = point.y;
				next.x = point.x + 1;
				draw_x_axis(args, apply_rotate(args, point, center), apply_rotate(args, next, center));
			}
			if (point.y + 1 < args->size_y)
			{
				next.z = args->map[(int)point.y + 1][(int)point.x];
				next.y = point.y + 1;
				next.x = point.x;
				draw_y_axis(args, apply_rotate(args, point, center), apply_rotate(args, next, center));
			}
			point.x += 1;
		}
		point.y += 1;
	}
}
