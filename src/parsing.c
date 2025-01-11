/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 01:46:42 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/11 02:01:04 by sacgarci         ###   ########.fr       */
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
		while (line[i] && ((line[i] != '-' && line[i] != '+')
			|| !ft_isdigit(line[i + 1])) && !ft_isdigit(line[i]))
			++i;
		if (!line[i])
			break ;
		++n;
		if (line[i] == '-' || line[i] == '+')
			++i;
		while (ft_isdigit(line[i]))
			++i;
	}
	return (n);
}

static int	*put_in_tab(char *line, t_args *args)
{
	int	*tab;
	int	n;
	int	i;

	tab = malloc(count_numbers(line) * sizeof(int));
	if (!tab)
		exit_msg(args, "Failed to alloc tab", 1, 1);
	i = 0;
	n = 0;
	while (line[i])
	{
		while (line[i] && ((line[i] != '-' && line[i] != '+')
			|| !ft_isdigit(line[i + 1])) && !ft_isdigit(line[i]))
			++i;
		if (!line[i])
			break ;
		tab[n] = ft_atoi(&line[i]);
		++n;
		if (line[i] == '-' || line[i] == '+')
			++i;
		while (ft_isdigit(line[i]))
			++i;
	}
	args->size_x = n;
	return (tab);
}

static t_map	*alloc_rows(t_args *args)
{
	t_map	*node;

	node = malloc(sizeof(t_map));
	if (!node)
		exit_msg(args, "Failed to alloc a node", 1, 1);
	node->next = NULL;
	node->row = NULL;
	return (node);
}

static void	read_map(t_args *args, t_map **start)
{
	char	*line;
	int		n;
	t_map	*map;

	map = *start;
	n = 1;
	line = get_next_line(args->fd);
	while (1)
	{
		map->row = put_in_tab(line, args);
		free(line);
		line = get_next_line(args->fd);
		if (!line)
			break ;
		map->next = alloc_rows(args);
		++n;
		map = map->next;
	}
	args->size_y = n;
	map->next = NULL;
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
	args->map = malloc(sizeof(t_map));
	if (!args->map)	
		exit_msg(args, "Failed to alloc map", 1, 1);
	read_map(args, &args->map);
	return (args);
}
