# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncarrera <ncarrera@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/21 22:44:05 by ncarrera          #+#    #+#              #
#    Updated: 2026/06/21 22:44:07 by ncarrera         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program requirements and settings as per the spec
NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./headers -I./minilibx-linux -I./get_next_line -I./ft_printf

# Linker flags eg. for readline
LDFLAGS = -L./ft_printf -lftprintf -L./minilibx-linux -lmlx -lXext -lX11 -lm -lz

# Libraries and project declarations
MLX = ./minilibx-linux/libmlx.a
FT_PRINTF = ./ft_printf/libftprintf.a
SRCS =	src/core/error_free.c \
		src/core/main.c \
		src/core/ft_init.c \
		src/parsing/map.c \
		src/parsing/checker.c \
		src/parsing/checker_utils.c \
		src/parsing/flood_fill.c \
		src/engine/game.c \
		src/engine/raycast/raycast.c \
		src/engine/raycast/raycast_init.c \
		src/engine/raycast/raycast_dda.c \
		src/engine/raycast/raycast_texture.c \
		src/engine/raycast/raycast_draw.c \
		src/engine/ft_move.c \
		src/utils/libft.c \
		src/utils/utils.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

# Colours
NC=\033[0m
Purple=\033[0;35m
Cyan=\033[1;36m
Red=\033[0;31m
LC=\033[2K

# Make rules and PHONY declarations
all: $(NAME)

$(NAME): $(MLX) $(FT_PRINTF) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(MLX):
	@make -C minilibx-linux -s

$(FT_PRINTF):
	@make -C ft_printf -s

%.o: %.c
	@printf "$(Cyan)Compiling: $(Purple)$<$(NC)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(Red)Deleting: $(Purple)$(OBJS)$(NC)\n"
	@rm -f $(OBJS)
	@make clean -C minilibx-linux -s
	@make clean -C ft_printf -s

fclean: clean
	@printf "$(Red)Deleting: $(Purple)$(NAME)$(NC)\n"
	@rm -f $(NAME)
	@make fclean -C ft_printf -s

re: fclean all
reclean:
	@$(MAKE) re -s
	@$(MAKE) clean -s

.PHONY: all clean fclean re reclean
