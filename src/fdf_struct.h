/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 02:42:14 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/28 16:24:45 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_STRUCT_H
# define FDF_STRUCT_H

# define HEIGHT 1080
# define LENGTH 1920

# include "mlx.h"
# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>

enum
{
	MOUSE_L = 1,
	MOUSE_M = 2,
	MOUSE_R = 3,
	SCROLL_U = 4,
	SCROLL_D = 5,
	ESC = 65307,
	ARROW_U = 65362,
	ARROW_D = 65364,
	ARROW_R = 65361,
	ARROW_L = 65363,
	NUM_7 = 65432,
	NUM_4 = 65429,
	NUM_9 = 65437,
	NUM_6 = 65434,
	W = 119,
	S = 115,
	D = 100,
	A = 97,
	C = 99,
	SPACE = 32,
	KEYDOWN = 2,
	KEYUP = 3,
	MOUSE_MOVE = 6,
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

typedef struct s_colors
{
	int	***tab;
	int	tab_size;
	int	i;
}	t_colors;

typedef struct s_args
{
	t_vars		*vars;
	t_img		*img;
	t_colors	*colors;
	t_2_vectors	last_pos;
	t_2_vectors	rotates;
	void		(*f)(struct s_args *, t_3_vectors, t_3_vectors, int color);
	int			**map;
	char		*file;
	float		highest;
	float		lowest;
	float		diff;
	float		height;
	float		scale;
	float		cos_val;
	float		sin_val;
	int			fd;
	int			start_x;
	int			start_y;
	int			size_x;
	int			size_y;
	int			button;
}	t_args;

#endif
