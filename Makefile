# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 02:15:19 by sacgarci          #+#    #+#              #
#    Updated: 2025/01/28 02:31:25 by sacgarci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = fdf
NAME_BONUS = fdf_bonus
SRCS = src/draw.c src/fdf.c src/parsing_utils.c src/exit_n_free.c src/parsing.c \
		src/window_gestion.c
SRCS_BONUS = src_bonus/calc_points_bonus.c src_bonus/rotates_bonus.c 			\
			src_bonus/parsing_utils_bonus.c src_bonus/exit_n_free_bonus.c		\
			src_bonus/fdf_bonus.c src_bonus/parsing_bonus.c 					\
			src_bonus/keyboard_gestion_bonus.c src_bonus/mouse_gestion_bonus.c	\
			src_bonus/draw_bonus.c src_bonus/colors_bonus.c
HEADER = src/fdf.h
HEADER_BONUS = src_bonus/fdf_bonus.h
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g -I libft -I minilibx-linux
MLX = minilibx-linux/libmlx.a
LDFLAGS =  $(LIBFT) $(MLX) $(shell pkg-config --libs x11 xext)

LIBFT = libft/libft.a

all:$(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME) -lm

bonus: $(OBJS_BONUS) $(LIBFT) $(MLX)
	$(CC) $(OBJS_BONUS) $(LDFLAGS) -o $(NAME_BONUS) -lm

%.o : %.c $(HEADER_BONUS) $(HEADER)
	$(CC) $(CFLAGS) $< -c -o $@

$(LIBFT):
	make -C libft

$(MLX):
	make -C minilibx-linux

run: all
	./$(NAME) test_maps/42.fdf

fclean: clean
	rm -f $(NAME) $(NAME_BONUS) $(LIBFT) $(MLX)

clean:
	make clean -C libft
	make clean -C minilibx-linux
	rm -f $(OBJS_BONUS) $(OBJS)

re: fclean all

.PHONY: all fclean clean run run2 re
