/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_n_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 23:02:22 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/27 23:23:57 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	exit_miss_args(void)
{
	write(2, "Usage :\n./fdf <FILE>\n", 21);
	exit (1);
}

static void	free_args(t_args *args, int to_free)
{
	if (to_free > 10)
		mlx_destroy_window(args->vars->mlx, args->vars->window);
	if (to_free > 9)
	{
		mlx_destroy_display(args->vars->mlx);
		free(args->vars->mlx);
	}
	if (to_free > 4)
		free(args->map);
	if (to_free > 5 && args->colors->tab)
		free(args->colors->tab);
	if (to_free > 8)
		free(args->img);
	if (to_free > 7)
		free(args->vars);
	if (to_free > 3)
		free(args->file);
	if (to_free > 1)
		free(args->colors);
	if (to_free > 0)
		free(args);
}

static void	ft_free(t_args *args, int to_free)
{
	int	i;
	int	j;

	i = 0;
	while (to_free > 6 && i < args->size_y && args->map[i])
	{
		free(args->map[i]);
		++i;
	}
	i = 0;
	while (to_free > 5 && args->colors->tab
		&& i < args->colors->tab_size && args->colors->tab[i])
	{
		j = 0;
		while (j < args->size_y && args->colors->tab[i][j])
		{
			free(args->colors->tab[i][j]);
			++j;
		}
		free(args->colors->tab[i]);
		++i;
	}
	free_args(args, to_free);
}

static void	display_format(void)
{
	write(2, "\n", 1);
	write(2, "Map format :\n", 13);
	write(2, "  <number>,<color> <space>...\\n\n", 32);
	write(2, "   <number>,<color> <space>...\\n\n\n", 34);
	write(2, "Number must be an integer (-2147483648 -> 2147483647).\n", 55);
	write(2, "Color must be preceded by a comma and must be in ", 49);
	write(2, "hexadecimal, beginning with '0x'.\nIt is not mandatory.\n\n", 56);
	write(2, "Example : 15,0xFF2108 14 8 2,0xFFFFFF\\n \n\n", 43);
}

void	exit_msg(t_args *args, char *msg, int close_fd, int status)
{
	if (close_fd > 2)
		close(args->fd);
	ft_free(args, close_fd);
	if (msg && ft_strncmp(msg, "Invalid Map", 11) == 0)
		display_format();
	else if (msg)
		perror(msg);
	exit(status);
}
