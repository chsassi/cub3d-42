NAME = cub3d

CC = cc
INCLUDES = ./libft.plus
CFLAGS = -Wextra -Werror -Wall -g -I$(INCLUDES)  -I. -Imlx
MLX_INCLUDE = -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz
AR = ar rc $(NAME)
RM = rm -f

RESET = $(shell tput sgr0)
BOLD_TEXT = $(shell tput bold)
ITALIC_TEXT = $(shell tput sitm)
COLOUR_BLUE = \033[0;34m
COLOUR_GREEN = \033[0;32m

LIBFT_MAKE = ./libft.plus
MLX_MAKE = ./mlx

SRC = ./src/algo/calculate.c \
	./src/algo/raycast_helpers.c \
	./src/algo/raycast.c \
	./src/game/event.c \
	./src/game/minimap.c \
	./src/game/movement.c \
	./src/game/rotation.c \
	./src/game/start_game.c \
	./main.c \
	./src/parsing/get_elements.c \
	./src/parsing/get_map.c \
	./src/parsing/get_player.c \
	./src/parsing/get_texture_and_colors.c \
	./src/parsing/init_all.c \
	./src/parsing/playability.c \
	./src/parsing/utils.c \
	./src/print/print_error.c \
	./src/utils/draw_helpers.c \
	./src/utils/drawing.c \
	./src/utils/free.c \

all: $(NAME)

$(NAME): $(SRC) 
	@make all -s -C $(LIBFT_MAKE)
	$(CC) $(CFLAGS) $(SRC) -L$(LIBFT_MAKE) -lft $(MLX_INCLUDE) -o $(NAME)
	@echo "$(COLOUR_BLUE) $(BOLD_TEXT) Run ./cub3d to start the game. $(RESET)";

clean:
	@make clean -s -C $(LIBFT_MAKE)

fclean: clean
	@make fclean -s -C $(LIBFT_MAKE)
	@$(RM) $(NAME)

re: fclean all

# .SILENT:
.PHONY: all clean fclean re