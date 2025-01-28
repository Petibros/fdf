/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 02:42:14 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/28 02:35:40 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "fdf_struct.h"

t_3_vectors	apply_rotate(t_args *args, t_3_vectors points);
int			***alloc_tab(t_args *args);
int			render_frame(t_args *args);
int			mouse_movement(int x, int y, t_args *args);
int			mouse_reset(int x, int y, t_args *args);
int			mouse_gestion(int button, int x, int y, t_args *args);
int			key_switch(int keycode, t_args *args);
int			close_window(t_args *args);
int			get_longest(t_args *args);
void		draw_iso(t_args *args, t_3_vectors points,
				t_3_vectors next, int color);
void		draw_curv(t_args *args, t_3_vectors points,
				t_3_vectors next, int color);
void		draw_line(t_args *args, t_2_vectors coords_1,
				t_2_vectors coords_2, int color);
void		my_mlx_pixel_put(t_img *data, int x, int y, int color);
void		get_z_ends(t_args *args, int n);
void		get_colors(t_args *args);
void		put_in_tab(char *line, t_args *args, int *tab, int y);
void		center_map(t_args *args);
void		get_rotates(t_args *args, int keycode);
void		change_height(t_args *args, int keycode);
void		print_map(t_args *args);
void		reset_image(t_img *image);
void		exit_miss_args(void);
void		exit_msg(t_args *args, char *msg, int close_fd, int status);
void		parsing(char **argv, t_args *args);

#endif
