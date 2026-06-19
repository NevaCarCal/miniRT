NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_PATH = minilibx-linux
MLX_LIB = $(MLX_PATH)/libmlx.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lz

GNL_PATH = get_next_line
PRINTF_PATH = ft_printf
FT_PRINTF_LIB = $(PRINTF_PATH)/libftprintf.a

INCLUDES = -Iheaders -I$(MLX_PATH) -I$(GNL_PATH) -I$(PRINTF_PATH)

CFILES = \
	src/error_free.c \
	src/map.c \
	src/checker.c \
	src/main.c \
	src/checker_utils.c \
	src/ft_init.c \
	src/ft_move.c \
	src/flood_fill.c \
	src/game.c \
	src/raycast.c \
	src/libft.c \
	src/utils.c \
	$(GNL_PATH)/get_next_line.c \
	$(GNL_PATH)/get_next_line_utils.c

OBJECTS = $(CFILES:.c=.o)

all: $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_PATH)

$(FT_PRINTF_LIB):
	$(MAKE) -C $(PRINTF_PATH)

$(NAME): $(MLX_LIB) $(FT_PRINTF_LIB) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(FT_PRINTF_LIB) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(MLX_PATH) clean
	$(MAKE) -C $(PRINTF_PATH) clean
	rm -f $(OBJECTS)

fclean: clean
	$(MAKE) -C $(PRINTF_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
