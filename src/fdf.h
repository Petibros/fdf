/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 02:42:14 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/12 02:32:02 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define HEIGHT 720
# define LENGTH 1560

# include "mlx.h"
# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>

enum
{
	KEYDOWN = 2,
	KEYUP = 3,
	RESIZE = 25,
	DESTROY = 17
};

typedef struct s_3_vectors
{
	float	x;
	float	y;
	float	z;
}	t_3_vectors;

typedef struct s_2_vectors
{
	float	x;
	float	y;
}	t_2_vectors;

typedef struct s_img
{
	void	*image;
	char	*address;
	int		bpp;
	int		line_l;
	int		endian;
}	t_img;

typedef struct s_vars
{
	void	*mlx;
	void	*window;
}	t_vars;

typedef struct s_map
{
	int				*row;
	struct s_map	*next;
}	t_map;

typedef struct s_args
{
	int		fd;
	t_map	*map;
	t_vars	*vars;
	t_img	*img;
	int		x;
	int		y;
	int		scale;
	int		size_x;
	int		size_y;
}	t_args;

int		render_frame(t_args *args);
void	my_mlx_pixel_put(t_img *data, float x, float y, int color);
void	print_map(t_args *args, t_map **start);
void	reset_image(t_img *image);
int		key_switch(int keycode, t_args *args);
int		close_window(t_args *args);
void	exit_miss_args(void);
void	exit_msg(t_args *args, char *msg, int close_fd, int status);
t_args	*parsing(char **argv);

#endif
