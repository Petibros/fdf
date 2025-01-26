CC=cc
NAME = fdf 
SRCS = src/exit_n_free.c src/fdf.c src/parsing.c src/window_gestion.c src/draw.c src/map_alteration.c src/colors.c
HEADER = src/fdf.h
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g -I libft -I minilibx-linux
MLX = minilibx-linux/libmlx.a
LDFLAGS =  $(LIBFT) $(MLX) $(shell pkg-config --libs x11 xext)

LIBFT = libft/libft.a

all:$(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME) -lm

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) $< -c -o $@

$(LIBFT):
	make -C libft

$(MLX):
	make -C minilibx-linux

run: all
	./$(NAME) test_maps/42.fdf

sacha: all
	./$(NAME) $(ARGS) 


run2: all
	echo "do1"
	gnome-terminal

run3: all
	echo "156f15"

fclean: clean
	rm -f $(NAME) $(LIBFT) $(MLX)

clean:
	make clean -C libft
	make clean -C minilibx-linux
	rm -f $(OBJS)

re: fclean all

.PHONY: all fclean clean run run2 re
