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

int			key_switch(int keycode, t_args *args);
int			close_window(t_args *args);
int			get_longest(t_args *args);
void		put_in_tab(char *line, t_args *args, int *tab);
void		center_map(t_args *args);
void		print_map(t_args *args);
void		exit_miss_args(void);
void		exit_msg(t_args *args, char *msg, int close_fd, int status);
void		parsing(char **argv, t_args *args);

#endif
