/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_alteration.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 01:47:06 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/17 07:28:20 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_height(t_args *args, int keycode)
{
	if (keycode == 65361)
		args->height += fabsf((args->height / 50)) + 0.002;
	else
		args->height -= fabsf((args->height / 50)) + 0.002;
}

void	get_rotates(t_args *args, int keycode)
{
	if (keycode == 65432)
		args->rotates.z -= 1;
	else if (keycode == 65434)
		args->rotates.z += 1;
	else if (keycode == 65437)
		args->rotates.y -= 1;
	else if (keycode == 65431)
		args->rotates.y += 1;
	else if (keycode == 65430)
		args->rotates.x -= 1;
	else if (keycode == 65429)
		args->rotates.x += 1;
}

t_3_vectors	apply_rotate(t_args *args, t_3_vectors points)
{
	t_3_vectors	final_points;
	t_3_vectors	theta;

	theta.x = args->rotates.x * M_PI / 180;
	theta.y = args->rotates.y * M_PI / 180;
	theta.z = args->rotates.z * M_PI / 180;


	final_points.x = cosf(theta.z) * points.x - sinf(theta.z) * points.y;
	final_points.y = sinf(theta.z) * points.x + cosf(theta.z) * points.y;
	final_points.z = points.z;

	points.x = cosf(theta.y) * final_points.x + sinf(theta.y) * final_points.z;
	points.y = final_points.y;
	points.z = -sinf(theta.y) * final_points.x + cosf(theta.y) * final_points.z;

	final_points.x = points.x;
	final_points.y = cosf(theta.x) * points.y - sinf(theta.x) * points.z;
	final_points.z = sinf(theta.x) * points.y + cosf(theta.x) * points.z;
	return (final_points);
}
