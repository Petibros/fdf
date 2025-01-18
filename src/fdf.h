/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 02:42:14 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/18 10:24:26 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define HEIGHT 720
# define LENGTH 1320

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

typedef struct s_args
{
	int			fd;
	int			**map;
	t_vars		*vars;
	t_img		*img;
	float		height;
	t_2_vectors	last_pos;
	int			start_x;
	int			start_y;
	float		scale;
	t_3_vectors	rotates;
	int			size_x;
	int			size_y;
}	t_args;

int			mouse_translation(int x, int y, t_args *args);
int			mouse_reset(int x, int y, t_args *args);
int			mouse_gestion(int button, int x, int y, t_args *args);
void		get_rotates(t_args *args, int keycode);
t_3_vectors	apply_rotate(t_args *args, t_3_vectors points, t_2_vectors center);
void		change_height(t_args *args, int keycode);
void		draw_line(t_args *args, t_2_vectors coords_1, t_2_vectors coords_2);
int			render_frame(t_args *args);
void		my_mlx_pixel_put(t_img *data, int x, int y, int color);
void		print_map(t_args *args);
void		reset_image(t_img *image);
int			key_switch(int keycode, t_args *args);
int			close_window(t_args *args);
void		exit_miss_args(void);
void		exit_msg(t_args *args, char *msg, int close_fd, int status);
t_args		*parsing(char **argv);

#endif
