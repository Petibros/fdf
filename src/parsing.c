/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 01:46:42 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/16 01:16:55 by sacgarci         ###   ########.fr       */
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
		while (line[i] && (line[i] == ' ' || line[i] == '\n'))
			++i;
		if (!line[i])
			break ;
		++n;
		if (line[i] == '-' || line[i] == '+')
			++i;
		while (ft_isdigit(line[i]))
			++i;
		if (line[i] == ',')
		{
			while (line[i] && line[i] != ' ')
				++i;
		}
	}
	return (n);
}

static void	put_in_tab(char *line, t_args *args, int *tab)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (line[i])
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\n'))
			++i;
		if (!line[i])
			break ;
		tab[n] = ft_atoi(&line[i]);
		++n;
		if (line[i] == '-' || line[i] == '+')
			++i;
		while (ft_isdigit(line[i]))
			++i;
		if (line[i] == ',')
		{
			while (line[i] && line[i] != ' ')
				++i;
		}
	}
	args->size_x = n;
}

static void	read_map(t_args *args)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(args->fd);
	while (1)
	{
		args->map[i] = malloc(count_numbers(line) * sizeof(int));
		if (!args->map[i])
			exit_msg(args, "Failed to alloc tab", 1, 1);
		put_in_tab(line, args, args->map[i]);
		free(line);
		line = get_next_line(args->fd);
		if (!line)
			break ;
		++i;
	}
}

int	count_line(t_args *args, char *file)
{
	char	*line;
	int		n;

	n = 0;
	line = get_next_line(args->fd);
	while (line)
	{
		free(line);
		line = get_next_line(args->fd);
		++n;
	}
	close(args->fd);
	args->fd = open(file, O_RDONLY);
	args->size_y = n;
	return (n);
}

t_args	*parsing(char **argv)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		exit_msg(args, "Failed to alloc args", 0, 1);
	args->fd = open(argv[1], O_RDONLY);
	if (args->fd == -1)
		exit_msg(args, "Invalid file", 0, 1);
	args->map = malloc(count_line(args, argv[1]) * sizeof(int *));
	if (!args->map)
		exit_msg(args, "Failed to alloc map", 1, 1);
	read_map(args);
	return (args);
}
