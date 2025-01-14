/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:01:36 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/12 00:11:25 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	translation(t_args *args, int keycode)
{
	if (keycode == 119)
		args->y -= 10;
	else if (keycode == 97)
		args->x -= 10;
	else if (keycode == 115)
		args->y += 10;
	else
		args->x += 10;
}

static void	zoom(t_args *args, int keycode)
{
	if (keycode == 65362)
		args->scale += 2;
	else
		args->scale -= 2;
}

int	close_window(t_args *args)
{
	mlx_destroy_window(args->vars->mlx, args->vars->window);
	exit_msg(args, NULL, 1, 0);
	return (0);
}

int	key_switch(int keycode, t_args *args)
{
	if (keycode == 65307)
		close_window(args);
	else if (keycode == 65362 || keycode == 65364)
		zoom(args, keycode);
	else if (keycode == 119 || keycode == 100 || keycode == 115 || keycode == 97)
		translation(args, keycode);
//	printf("%d %d\n", args->x, args->y);
	return (0);
}
