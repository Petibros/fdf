/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_n_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 23:02:22 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/20 00:27:42 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_miss_args(void)
{
	write(2, "Usage :\n./fdf <FILE>\n", 21);
	exit (1);
}

static void	ft_free(t_args *args)
{
	int	i;
	int	j;

	i = 0;
	while (args && args->map && i < args->size_y && args->map[i])
	{
		free(args->map[i]);
		++i;
	}
	i = 0;
	while (args && args->colors && args->colors->tab && i < args->colors->tab_size && args->colors->tab[i])
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
	if (args && args->map)
		free(args->map);
	if (args && args->colors && args->colors->tab)
		free(args->colors->tab);
	if (args && args->colors)
		free(args->colors);
	if (args && args->img)
		free(args->img);
	if (args && args->vars)
		free(args->vars);
	if (args)
		free(args);
}

void	exit_msg(t_args *args, char *msg, int close_fd, int status)
{
	if (close_fd)
		close(args->fd);
	ft_free(args);
	if (msg)
		perror(msg);
	exit(status);
}
