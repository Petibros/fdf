/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 02:42:14 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/24 01:07:01 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define HEIGHT 960
# define LENGTH 1780

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

typedef struct s_colors
{
	int	***tab;
	int	tab_size;
	int	i;
}	t_colors;

typedef struct s_args
{
	int			fd;
	int			**map;
	t_colors	*colors;
	float		highest;
	float		lowest;
	float		diff;
	void		(*f)(struct s_args *, t_3_vectors, t_3_vectors, int color);
	t_vars		*vars;
	t_img		*img;
	float		height;
	t_2_vectors	last_pos;
	int			start_x;
	int			start_y;
	float		scale;
	t_2_vectors	rotates;
	int			size_x;
	int			size_y;
	int			button;
	float		cos_val;
	float		sin_val;
}	t_args;

void		get_colors(t_args *args);
int			***alloc_tab(t_args *args);
int			get_r(int color);
int			get_g(int color);
int			get_b(int color);
void		draw_iso(t_args *args, t_3_vectors points, t_3_vectors next, int color);
void		draw_curv(t_args *args, t_3_vectors points, t_3_vectors next, int color);
void		center_map(t_args *args);
int			mouse_movement(int x, int y, t_args *args);
int			mouse_reset(int x, int y, t_args *args);
int			mouse_gestion(int button, int x, int y, t_args *args);
void		get_rotates(t_args *args, int keycode);
t_3_vectors	apply_rotate(t_args *args, t_3_vectors points);
void		change_height(t_args *args, int keycode);
void		draw_line(t_args *args, t_2_vectors coords_1, t_2_vectors coords_2, int color);
int			render_frame(t_args *args);
void		my_mlx_pixel_put(t_img *data, int x, int y, int color);
void		print_map(t_args *args);
void		reset_image(t_img *image);
int			key_switch(int keycode, t_args *args);
int			close_window(t_args *args);
void		exit_miss_args(void);
void		exit_msg(t_args *args, char *msg, int close_fd, int status);
void		parsing(char **argv, t_args *args);

#endif
