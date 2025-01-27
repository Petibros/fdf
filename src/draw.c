/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 09:40:34 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/24 01:11:32 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset_image(t_img *image)
{
	t_2_vectors	coords;

	coords.y = 0;
	while (coords.y < HEIGHT)
	{
		coords.x = 0;
		while (coords.x < LENGTH)
		{
			my_mlx_pixel_put(image, coords.x, coords.y, 0x000000);
			coords.x += 1;
		}
		coords.y += 1;
	}
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x < LENGTH && x >= 0 && y < HEIGHT && y >= 0)
	{
		dst = data->address + (int)(y * data->line_l + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_line(t_args *args, t_2_vectors coords_1, t_2_vectors coords_2, int color)
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
		my_mlx_pixel_put(args->img,
			(int)coords_1.x, (int)coords_1.y, color);
		coords_1.x += step.x;
		coords_1.y += step.y;
		++i;
	}
}

void	draw_curv(t_args *args, t_3_vectors points, t_3_vectors next, int color)
{
	t_2_vectors	coords_1;
	t_2_vectors	coords_2;
	float		r;
	float		theta;
	float		phi;

	r = sqrtf(pow(points.x, 2) + pow(points.y, 2) + pow(points.z, 2));
	theta = atan2f(points.y, points.x);
	phi	= acosf(points.z / r);
	coords_1.x = r * theta * args->scale + args->start_x;	
	coords_1.y = r * phi * args->scale + args->start_y;
	r = sqrtf(pow(next.x, 2) + pow(next.y, 2) + pow(next.z, 2));
	theta = atan2f(next.y, next.x);
	phi	= acosf(next.z / r);
	coords_2.x = r * theta * args->scale + args->start_x;
	coords_2.y = r * phi * args->scale + args->start_y;
	draw_line(args, coords_1, coords_2, color);
}

void	draw_iso(t_args *args, t_3_vectors points, t_3_vectors next, int color)
{
	t_2_vectors	coords_1;
	t_2_vectors	coords_2;

	coords_1.x = ((points.x - points.y) * args->cos_val * args->scale) + args->start_x;
	coords_1.y = (points.x + points.y) * args->sin_val - points.z;
	coords_1.y = coords_1.y * args->scale + args->start_y;
	coords_2.x = ((next.x - next.y) * args->cos_val * args->scale) + args->start_x;
	coords_2.y = (next.x + next.y) * args->sin_val - next.z;
	coords_2.y = coords_2.y * args->scale + args->start_y;
	draw_line(args, coords_1, coords_2, color);
}

void	print_map(t_args *args)
{
	t_3_vectors	point;
	t_3_vectors	next;
	int			color;

	point.y = 0;
	while (point.y < args->size_y)
	{
		point.x = 0;
		while (point.x < args->size_x)
		{
			point.z = args->map[(int)point.y][(int)point.x] * args->height;
			if (point.x + 1 < args->size_x)
			{
				next.y = point.y;
				next.x = point.x + 1;
				next.z = args->map[(int)next.y][(int)next.x] * args->height;
				if (fmax(fabs(point.z / args->height), fabs(next.z / args->height)) == fabs(next.z / args->height))
					color = args->colors->tab[args->colors->i][(int)next.y][(int)next.x];
				else
					color = args->colors->tab[args->colors->i][(int)point.y][(int)point.x];
				args->f(args, apply_rotate(args, point), apply_rotate(args, next), color);
			}
			if (point.y + 1 < args->size_y)
			{
				next.y = point.y + 1;
				next.x = point.x;
				next.z = args->map[(int)next.y][(int)next.x] * args->height;	
				if (fmax(fabs(point.z / args->height), fabs(next.z / args->height)) == fabs(next.z / args->height))
					color = args->colors->tab[args->colors->i][(int)next.y][(int)next.x];
				else
					color = args->colors->tab[args->colors->i][(int)point.y][(int)point.x];
				args->f(args, apply_rotate(args, point), apply_rotate(args, next), color);
			}
			point.x += 1;
		}
		point.y += 1;
	}
}
