CC=cc
NAME = fdf 
SRCS = src/exit_n_free.c src/fdf.c src/parsing.c
HEADER = src/fdf.h
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g 
LDFLAGS =  $(LIBFT) $(shell pkg-config --libs x11 xext)
MLXFLAGS = $(MLX)

MLX = minilibx/libmlx.a

LIBFT = libft/libft.a

all:$(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(OBJS) $(LDFLAGS) $(MLXFLAGS) -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) $< -c -o $@

$(LIBFT):
	make -C libft

$(MLX):
	make -C minilibx

fclean: clean
	rm -f $(NAME) $(LIBFT) $(MLX)

clean:
	make clean -C libft
	make clean -C minilibx
	rm -f $(OBJS)

re: fclean all

.PHONY: all fclean clean run run2 re
