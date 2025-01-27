#include "fdf.h"

int	get_r(int color)
{
	return ((color >> 16) & 0xFF);
}

int	get_g(int color)
{
	return ((color >> 8) & 0xFF);
}

int	get_b(int color)
{
	return (color & 0xFF);
}

int ***alloc_tab(t_args *args)
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

void	get_colors(t_args *args)
{
	int	y;
	int	x;
	int	factor;
	int	base;

	factor = 0;
	base = -1;
	while (args->colors->i < 3)
	{
		y = 0;
		while (y < args->size_y)
		{
			x = 0;
			while (x < args->size_x)
			{
				args->colors->tab[args->colors->i][y][x] = base - (factor * fabsf((args->map[y][x] / args->diff)));
				++x;
			}
			++y;
		}
		++args->colors->i;
		factor = -255;
		base = 1;
		if (args->colors->i == 2)
			base = 16711680;
	}
	args->colors->i = 0;
}
