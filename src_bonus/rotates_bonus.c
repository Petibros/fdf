/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 01:47:06 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/28 18:01:52 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static t_3_vectors	rotate(t_args *args, t_3_vectors points,
		t_3_vectors axis, float theta)
{
	t_3_vectors	final_points;
	t_2_vectors	center;
	float		sinus;
	float		cosinus;

	center.x = args->size_x / 2;
	center.y = args->size_y / 2;
	sinus = sinf(theta);
	cosinus = cosf(theta);
	points.x -= center.x;
	points.y -= center.y;
	final_points.x = points.x * (cosinus + pow(axis.x, 2) * (1 - cosinus))
		+ points.y * (axis.x * axis.y * (1 - cosinus) - axis.z * sinus)
		+ points.z * (axis.x * axis.z * (1 - cosinus) + axis.y * sinus);
	final_points.y = points.x * (axis.y * axis.x * (1 - cosinus) + axis.z
			* sinus) + points.y * (cosinus + pow(axis.y, 2) * (1 - cosinus))
		+ points.z * (axis.y * axis.z * (1 - cosinus) - axis.x * sinus);
	final_points.z = points.x * (axis.z * axis.x * (1 - cosinus) - axis.y
			* sinus) + points.y * (axis.z * axis.y * (1 - cosinus) + axis.x
			* sinus) + points.z * (cosinus + pow(axis.z, 2) * (1 - cosinus));
	final_points.x += center.x;
	final_points.y += center.y;
	return (final_points);
}

t_3_vectors	apply_rotate(t_args *args, t_3_vectors points)
{
	t_3_vectors	axis;

	axis.x = -1 / sqrt(2);
	axis.y = 1 / sqrt(2);
	axis.z = 0;
	points = rotate(args, points, axis, args->rotates.x * M_PI / 180);
	axis.x = 0;
	axis.y = 0;
	axis.z = 1;
	return (rotate(args, points, axis, args->rotates.y * M_PI / 180));
}
