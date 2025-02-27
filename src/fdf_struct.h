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
	ESC = 65307,
	KEYDOWN = 2,
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

typedef struct s_args
{
	t_vars		*vars;
	t_img		*img;
	int			**map;
	char		*file;
	float		highest;
	float		lowest;
	float		scale;
	float		cos_val;
	float		sin_val;
	int			fd;
	int			start_x;
	int			start_y;
	int			size_x;
	int			size_y;
}	t_args;

#endif
