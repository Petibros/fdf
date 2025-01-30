/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:07:29 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/28 02:24:19 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	***alloc_tab(t_args *args)
{
	int	***tab;
	int	i;
	int	j;

	i = 0;
	tab = malloc(args->colors->tab_size * sizeof(int **));
	if (!tab)
		exit_msg(args, "Failed to alloc colors", 1, 1);
	while (i < args->colors->tab_size)
	{
		j = 0;
		tab[i] = malloc(args->size_y * sizeof(int *));
		if (!tab[i])
			exit_msg(args, "Failed to alloc colors", 1, 1);
		while (j < args->size_y)
		{
			tab[i][j] = ft_calloc(args->size_x, sizeof(int));
			if (!tab[i][j])
				exit_msg(args, "Failed to alloc colors", 1, 1);
			++j;
		}
		++i;
	}
	return (tab);
}

static void	set_gradiant_ends(t_args *args, int *factor, int *end)
{
	*factor = -255;
	if (args->colors->i == 1)
		*end = 65536;
	if (args->colors->i == 2)
	{
		*end = 16711730;
		*factor = -65280;
	}
	if (args->colors->i == 3)
		*end = 65280;
	if (args->colors->i == 4)
	{
		*end = 65330;
		*factor = -65280;
	}
	if (args->colors->i == 5)
		*end = 8552445;
	if (args->colors->i == 6)
		*end = 16776960;
}

void	get_colors(t_args *args)
{
	int	y;
	int	x;
	int	factor;
	int	end;

	factor = 0;
	end = -1;
	while (args->colors->i < 7)
	{
		y = 0;
		while (y < args->size_y)
		{
			x = 0;
			while (x < args->size_x)
			{
				args->colors->tab[args->colors->i][y][x]
					= end - (factor * fabsf((args->map[y][x] / args->diff)));
				++x;
			}
			++y;
		}
		++args->colors->i;
		set_gradiant_ends(args, &factor, &end);
	}
	args->colors->i = 0;
}
