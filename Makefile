# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yel-bouk <yel-bouk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/22 15:13:25 by yel-bouk          #+#    #+#              #
#    Updated: 2025/02/11 12:53:57 by yel-bouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS = main.c \
		keys.c \
		main_utils.c \
		cleanup.c \
		keys_utils.c \
		maps/map_handler.c \
		maps/map_parser_utils.c \
		maps/map_floodfill.c \
		maps/map_utils.c \
		maps/map_validator.c \
		maps/map_parser.c \
       	GNL/get_next_line.c \
      	GNL/get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_REPO = https://github.com/42Paris/minilibx-linux.git
LIBFTPRINTF_DIR = ./ft_printf
LIBFTPRINTF = $(LIBFTPRINTF_DIR)/libftprintf.a


# Detect OS
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	INCLUDES = -I$(MLX_DIR)
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11
else ifeq ($(UNAME), Darwin)
	INCLUDES = -I/opt/X11/include -Imlx
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

# Default target
all: $(MLX_LIB) $(LIBFTPRINTF) $(NAME)

# Compile .c to .o
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

# Link executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFTPRINTF) $(MLX_FLAGS)

$(MLX_DIR):
	git clone $(MLX_REPO) $(MLX_DIR)

$(MLX_LIB): $(MLX_DIR)
	@make -C $(MLX_DIR)

# Build MiniLibX
$(MLX_LIB):
	@make -C $(MLX_DIR)

# Clean object files
clean:
	$(RM) $(OBJS)

# Full clean
fclean: clean
	$(RM) $(NAME)
	$(RM) -r $(MLX_DIR)


# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
