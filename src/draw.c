/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:40:34 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/28 18:15:49 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x < LENGTH && x >= 0 && y < HEIGHT && y >= 0)
	{
		dst = data->address + (int)(y * data->line_l + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

static void	draw_line(t_args *args, t_2_vectors coords_1,
		t_2_vectors coords_2, int color)
{
	int			n;
	t_2_vectors	diff;
	int			i;
	t_2_vectors	step;

	if (color == 0)
		color = -1;
	i = 0;
	step.x = coords_2.x - coords_1.x;
	step.y = coords_2.y - coords_1.y;
	diff.x = fabsf(step.x);
	diff.y = fabsf(step.y);
	if (diff.x >= diff.y)
		n = diff.x;
	else
		n = diff.y;
	step.x = step.x / n;
	step.y = step.y / n;
	while (i <= n)
	{
		my_mlx_pixel_put(args->img, (int)coords_1.x, (int)coords_1.y, color);
		coords_1.x += step.x;
		coords_1.y += step.y;
		++i;
	}
}

static void	draw_iso(t_args *args, t_3_vectors points, t_3_vectors next)
{
	t_2_vectors	coords_1;
	t_2_vectors	coords_2;

	coords_1.x = ((points.x - points.y) * args->cos_val * args->scale)
		+ args->start_x;
	coords_1.y = (points.x + points.y) * args->sin_val - points.z;
	coords_1.y = coords_1.y * args->scale + args->start_y;
	coords_2.x = ((next.x - next.y) * args->cos_val * args->scale)
		+ args->start_x;
	coords_2.y = (next.x + next.y) * args->sin_val - next.z;
	coords_2.y = coords_2.y * args->scale + args->start_y;
	draw_line(args, coords_1, coords_2, 0xFFFFFF);
}

void	print_map(t_args *args)
{
	t_3_vectors	point;

	point.y = 0;
	while (point.y < args->size_y)
	{
		point.x = 0;
		while (point.x < args->size_x)
		{
			point.z = args->map[(int)point.y][(int)point.x];
			if (point.x + 1 < args->size_x)
			{
				draw_iso(args, point, (t_3_vectors){point.x + 1, point.y,
					args->map[(int)point.y][(int)point.x + 1]});
			}
			if (point.y + 1 < args->size_y)
			{
				draw_iso(args, point, (t_3_vectors){point.x, point.y + 1,
					args->map[(int)point.y + 1][(int)point.x]});
			}
			point.x += 1;
		}
		point.y += 1;
	}
}
