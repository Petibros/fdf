/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 01:46:42 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/23 21:04:04 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	count_numbers(char *line)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			++i;
		if (!line[i] || line[i] == '\n')
			break ;
		++n;
		if (line[i] == '-' || line[i] == '+')
			++i;
		while (ft_isdigit(line[i]))
			++i;
		if (line[i] == ',')
		{
			while (line[i] && line[i] != '\n' && line[i] != ' ')
				++i;
		}
	}
	return (n);
}

static int	get_longest(char *file)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (file[i])
	{
		if (count_numbers(&file[i]) > n)
			n = count_numbers(&file[i]);
		while (file[i] && file[i] != '\n')
			++i;
		if (file[i] == '\n')
			++i;
	}
	return (n);
}

static void	put_in_tab(char *line, t_args *args, int *tab, int y)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			++i;
		if (!line[i] || line[i] == '\n')
			break ;
		tab[n] = ft_atoi(&line[i]);
		if (tab[n] > args->highest)
			args->highest = tab[n];
		if (tab[n] < args->lowest)
			args->lowest = tab[n];
		++n;
		if (line[i] == '-' || line[i] == '+')
			++i;
		while (ft_isdigit(line[i]))
			++i;
		if (line[i] == ',')
		{
			while (line[i] && line[i] != '\n' && line[i] != ' ')
			{
				if (line[i] == '0' && line[i + 1] == 'x')
					args->colors[y][n - 1] = ft_atoi_base(&line[i + 2], "0123456789abcdef");
				if (line[i] == '0' && line[i + 1] == 'X')
					args->colors[y][n - 1] = ft_atoi_base(&line[i + 2], "0123456789ABCDEF");
				++i;
			}
		}
	}
	while (n < args->size_x)
		tab[n++] = 0;
}

static void	fill_tab(t_args *args, char *file)
{
	int		i;
	int		n;

	n = 0;
	i = 0;
	args->size_x = get_longest(file);
	while (args->colors && i < args->size_y)
	{
		args->colors[i] = ft_calloc(args->size_x, sizeof(int));
		if (!args->colors[i])
			exit_msg(args, "Malloc error when trying to alloc colors", 1, 1);
		++i;
	}
	i = 0;
	while (file[i])
	{
		args->map[n] = malloc(args->size_x * sizeof(int));
		if (!args->map[n])
			exit_msg(args, "Failed to alloc tab", 1, 1);
		put_in_tab(&file[i], args, args->map[n], n);
		while (file[i] && file[i] != '\n')
			++i;
		if (file[i] == '\n')
			++i;
		++n;
	}
	free(file);
}

static char	*read_map(t_args *args)
{
	int		i;
	char	buffer[4096];
	char	*file;
	char	*tmp;
	int		n_read;

	i = 0;
	file = ft_calloc(1, sizeof(char));
	n_read = read(args->fd, buffer, 4095);
	while (n_read)
	{
		buffer[n_read] = 0;
		tmp = ft_strdup(file);
		if (!tmp || !file)
			exit_msg(args, "Malloc error whilst reading map", 1, 1);
		free(file);
		file = ft_strjoin(tmp, buffer);
		free(tmp);
		n_read = read(args->fd, buffer, 4095);
	}
	while (file[i])
	{
		if (file[i] == '\n')
			++args->size_y;
		if (file[i] == '0' && (file[i + 1] == 'x' || file[i + 1] == 'X'))
			n_read = 1;
		++i;
	}
	if (i >= 1 && file[i - 1] != '\n')
		++args->size_y;
	if (n_read)
	{
		args->colors = malloc(args->size_y * sizeof(int *));
		if (!args->colors)
			exit_msg(args, "Malloc error when trying to alloc colors", 1, 1);
	}
	return (file);
}

t_args	*parsing(char **argv)
{
	t_args	*args;
	char	*file;

	args = malloc(sizeof(t_args));
	if (!args)
		exit_msg(args, "Failed to alloc args", 0, 1);
	args->fd = open(argv[1], O_RDONLY);
	if (args->fd == -1)
		exit_msg(args, "Invalid file", 0, 1);
	args->size_y = 0;
	args->highest = 0;
	args->lowest = 0;
	file = read_map(args);
	args->map = malloc(args->size_y * sizeof(int *));
	if (!args->map)
		exit_msg(args, "Failed to alloc map", 1, 1);
	fill_tab(args, file);
	return (args);
}
