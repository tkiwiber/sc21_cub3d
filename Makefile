NAME = cub3D

CC = gcc

CFLAGS = -O3 -Wall -Wextra -Werror

MLX = mlxopengl

LXFLAGS = -lmlx -framework OpenGL -framework AppKit

HEADER = cub3d.h

SRC = checkup \
	cub3d \
	draw \
	draw_shapes \
	frame \
	gnl \
	gnl_utils \
	init \
	key_handle \
	map \
	minimap \
	movements \
	raycast \
	save_bmp \
	setup \
	sprites \
	texture \
	tools \

FIL = $(addsuffix .c, $(addprefix srsc/, $(SRC)))

OBJ = $(FIL:.c=.o)

BIN = $(addsuffix .o, $(SRC))

.PHONY: all clean fclean re bmp norm

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n\033[0;33mCompiling..."
	$(CC) -o $(NAME) -L $(MLX) $(LXFLAGS) $(OBJ)
	@echo "\033[0m"

clean:
	@echo "\033[0;31mCleaning..."
	rm -rf $(OBJ) $(B_OBJ)
	rm -f bitmap.bmp
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
