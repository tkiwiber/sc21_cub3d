NAME = cub3D

CC = gcc

CFLAGS = -g -O3 #-Wall -Wextra -Werror

MLX = mlxopengl

LXFLAGS = -lmlx -framework OpenGL -framework AppKit

HEADER = cub3d.h

B_HEADER = cub3d_bonus.h

SRC = cub3d \
	draw \
	draw_shapes \
	frame \
	gnl \
	gnl_utils \
	init \
	key_handle \
	load \
	map \
	minimap \
	movements \
	raycast \
	setup \
	sprites \
	texture \
	tools \

FIL = $(addsuffix .c, $(addprefix srsc/, $(SRC)))

OBJ = $(FIL:.c=.o)

BIN = $(addsuffix .o, $(SRC))

B_HEADER = cub3d_bonus.h

B_SRC = screen_row \
	sprite_draw \
	key_more \
	weapons \
	enemy \
	door \
	hud \

B_FIL = $(addsuffix _bonus.c, $(addprefix bonus/, $(SRC) $(B_SRC)))

B_OBJ = $(B_FIL:.c=.o)

B_BIN = $(addsuffix _bonus.o, $(SRC) $(B_SRC))

.PHONY: all clean fclean re bonus test sqr bmp err inv norm

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
	./$(NAME) maps/wowo.cub  

bonus: fclean $(B_OBJ)
	@echo "\n\033[0;32mCompiling bonus..."
	$(CC) -o $(NAME) -L $(MLX) $(LXFLAGS) $(B_OBJ)
	@echo "\033[0m"

	./$(NAME)

test: re
	./$(NAME) maps/map.cub

sqr: re
	./$(NAME) maps/sqr.cub

bmp: re
	./$(NAME) maps/map.cub --save

err: re
	./$(NAME) maps/none

inv: re
	./$(NAME) maps/inv.cub

norm:
	norminette $(FIL) $(B_FIL) srcs/$(HEADER) bonus/$(B_HEADER)
