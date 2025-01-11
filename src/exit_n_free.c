/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_n_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 23:02:22 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/11 00:21:45 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_miss_args()
{
	write(2, "Usage :\n./fdf <FILE>\n", 21);
	exit (1);
}

static void	ft_free(t_args *args)
{
	int	i;
	t_map	*node;

	i = 0;
	while (args && args->map)
	{
		if (args->map->row)
			free(args->map->row);
		node = args->map->next;
		free(args->map);
		args->map = node;
	}
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
