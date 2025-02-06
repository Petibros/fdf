/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 01:46:42 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/28 02:33:54 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	fill_tab(t_args *args)
{
	int		i;
	int		n;

	n = 0;
	i = 0;
	args->size_x = get_longest(args);
	args->colors->tab = alloc_tab(args);
	i = 0;
	while (args->file[i])
	{
		args->map[n] = malloc(args->size_x * sizeof(int));
		if (!args->map[n])
			exit_msg(args, "Failed to alloc tab", 7, 1);
		put_in_tab(&args->file[i], args, args->map[n], n);
		while (args->file[i] && args->file[i] != '\n')
			++i;
		if (args->file[i] == '\n')
			++i;
		++n;
	}
}

static char	*read_map(t_args *args)
{
	char	buffer[4096];
	char	*file;
	char	*tmp;
	int		n_read;

	file = ft_calloc(1, sizeof(char));
	n_read = read(args->fd, buffer, 4095);
	while (n_read)
	{
		if (!file)
			exit_msg(args, "Malloc error whilst reading map", 3, 1);
		buffer[n_read] = 0;
		tmp = ft_strdup(file);
		free(file);
		if (!tmp)
			exit_msg(args, "Malloc error whilst reading map", 3, 1);
		file = ft_strjoin(tmp, buffer);
		free(tmp);
		n_read = read(args->fd, buffer, 4095);
	}
	return (file);
}

static void	count_lines(t_args *args)
{
	int	i;
	int	set_colors;

	i = 0;
	set_colors = 0;
	while (args->file[i])
	{
		if (args->file[i] == '\n')
			++args->size_y;
		if (args->file[i] == '0'
			&& (args->file[i + 1] == 'x' || args->file[i + 1] == 'X'))
			set_colors = 1;
		++i;
	}
	if (i >= 1 && args->file[i - 1] != '\n')
		++args->size_y;
	if (set_colors)
		args->colors->tab_size++;
}

void	parsing(char **argv, t_args *args)
{
	args->fd = open(argv[1], O_RDONLY);
	if (args->fd == -1)
		exit_msg(args, "Invalid file", 2, 1);
	args->size_y = 0;
	args->highest = 0;
	args->lowest = 0;
	args->file = read_map(args);
	count_lines(args);
	args->map = malloc(args->size_y * sizeof(int *));
	if (!args->map)
		exit_msg(args, "Failed to alloc map", 4, 1);
	fill_tab(args);
}
