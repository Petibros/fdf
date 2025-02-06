/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 02:25:01 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/28 02:35:27 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_z_ends(t_args *args, int n)
{
	if (n > args->highest)
		args->highest = n;
	if (n < args->lowest)
		args->lowest = n;
}

static int	skip_map_colors(char *line)
{
	int	i;

	i = 0;
	if (line[i] == ',')
	{
		while (line[i] && line[i] != '\n' && line[i] != ' ')
			++i;
	}
	return (i);
}

void	put_in_tab(char *line, t_args *args, int *tab)
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
		get_z_ends(args, tab[n]);
		++n;
		if (line[i] == '-' || line[i] == '+')
			++i;
		while (ft_isdigit(line[i]))
			++i;
		i += skip_map_colors(&line[i]);
	}
	while (n < args->size_x)
	{
		tab[n] = 0;
		++n;
	}
}

static int	count_numbers(char *line, t_args *args)
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
		if (!ft_isdigit(line[i]) && line[i] != '-' && line[i] != '+')
			exit_msg(args, "Invalid Map", 5, 1);
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

int	get_longest(t_args *args)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (args->file[i])
	{
		if (count_numbers(&args->file[i], args) > n)
			n = count_numbers(&args->file[i], args);
		while (args->file[i] && args->file[i] != '\n')
			++i;
		if (args->file[i] == '\n')
			++i;
	}
	return (n);
}
