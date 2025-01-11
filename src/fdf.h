/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 02:42:14 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/11 02:52:09 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>

enum
{
	KEYDOW = 2,
	KEYUP = 3,
	RESIZE = 25,
	DESTROY = 17
};

typedef	struct s_img
{
	void	*image;
	char	*address;
	int		bpp;
	int		line_l;
	int		endian;
}	t_img;

typedef	struct s_vars
{	
	void	*mlx;
	void	*window;
}	t_vars;

typedef	struct s_map
{
	int				*row;
	struct s_map	*next;
}	t_map;

typedef	struct s_args
{
	int		fd;
	t_map	*map;
	t_vars	*vars;
	t_img	*img;
	int		size_x;
	int		size_y;
}	t_args;

void	exit_miss_args();
void	exit_msg(t_args *args, char *msg, int close_fd, int status);
t_args	*parsing(char **argv);

#endif
