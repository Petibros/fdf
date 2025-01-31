/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:43:42 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/28 18:03:04 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	draw_curv(t_args *args, t_3_vectors points, t_3_vectors next, int color)
{
	t_2_vectors	coords_1;
	t_2_vectors	coords_2;
	float		r;
	float		theta;
	float		phi;

	r = sqrtf(pow(points.x, 2) + pow(points.y, 2) + pow(points.z, 2));
	theta = atan2f(points.y, points.x);
	phi = acosf(points.z / r);
	coords_1.x = r * theta * args->scale + args->start_x;
	coords_1.y = r * phi * args->scale + args->start_y;
	r = sqrtf(pow(next.x, 2) + pow(next.y, 2) + pow(next.z, 2));
	theta = atan2f(next.y, next.x);
	phi = acosf(next.z / r);
	coords_2.x = r * theta * args->scale + args->start_x;
	coords_2.y = r * phi * args->scale + args->start_y;
	draw_line(args, coords_1, coords_2, color);
}

void	draw_iso(t_args *args, t_3_vectors points, t_3_vectors next, int color)
{
	t_2_vectors	coords_1;
	t_2_vectors	coords_2;
	float		cos_val;
	float		sin_val;

	sin_val = sinf(30 * M_PI / 180);
	cos_val = cosf(30 * M_PI / 180);
	coords_1.x = ((points.x - points.y) * cos_val * args->scale)
		+ args->start_x;
	coords_1.y = (points.x + points.y) * sin_val - points.z;
	coords_1.y = coords_1.y * args->scale + args->start_y;
	coords_2.x = ((next.x - next.y) * cos_val * args->scale)
		+ args->start_x;
	coords_2.y = (next.x + next.y) * sin_val - next.z;
	coords_2.y = coords_2.y * args->scale + args->start_y;
	draw_line(args, coords_1, coords_2, color);
}

void	draw_cava(t_args *args, t_3_vectors points, t_3_vectors next, int color)
{
	t_2_vectors	coords_1;
	t_2_vectors	coords_2;
	float		cos_val;
	float		sin_val;

	cos_val = cosf(45 * M_PI / 180);
	sin_val = sinf(45 * M_PI / 180);
	coords_1.x = ((points.x + cos_val * points.y)
			* args->scale) + args->start_x;
	coords_1.y = ((-points.z + sin_val * points.y)
			* args->scale) + args->start_y;
	coords_2.x = ((next.x + cos_val * next.y) * args->scale) + args->start_x;
	coords_2.y = ((-next.z + sin_val * next.y) * args->scale) + args->start_y;
	draw_line(args, coords_1, coords_2, color);
}
