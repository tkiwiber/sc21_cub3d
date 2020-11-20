NAME = cub3D

CC = gcc

CFLAGS = -O3 -Wall -Wextra -Werror

MLX = mlxopengl

LXFLAGS = -lmlx -framework OpenGL -framework AppKit

HEADER = cub3d.h

SRC = checkup \
	cub3d \
	draw \
	frame \
	gnl \
	gnl_utils \
	init1 \
	init2 \
	init3 \
	key_handle \
	map \
	movements \
	raycast \
	save_bmp \
	setup \
	sprites \
	texture \
	tools \

SRC_MLX	= 	mlx_shaders.c \
			mlx_new_window.m \
			mlx_init_loop.m \
			mlx_new_image.m \
			mlx_xpm.c \
			mlx_int_str_to_wordtab.c \
			mlx_png.c \
			mlx_mouse.m \

FIL = $(addsuffix .c, $(addprefix srcs/, $(SRC)))
FIL_MLX = $(addsuffix .c, $(addprefix mlxopengl/, $(SRC_MLX)))

OBJ = $(FIL:.c=.o)
OBJ_MLX = $(FIL_MLX:.m=.o)

BIN = $(addsuffix .o, $(SRC))

.PHONY: all clean fclean re bmp norm

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n\033[0;33mCompiling..."
	$(MAKE) -C $(MLX)
	$(CC) -o $(NAME) -L$(MLX) $(LXFLAGS) $(OBJ)
	@echo "\033[0m"

clean:
	@echo "\033[0;31mCleaning..."
	rm -rf $(OBJ)
	rm -rf $(OBJ_MLX)
	rm -rf libmlx.a
	rm -f screenshot.bmp
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mRemoving executable..."
	rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

run: re 
	./$(NAME) maps/123.cub

bmp: re
	./$(NAME) maps/123.cub --save

err: re
	./$(NAME) maps/none

norm:
	norminette $(FIL) srcs/$(HEADER)
