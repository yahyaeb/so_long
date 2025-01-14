# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yel-bouk <yel-bouk@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/22 15:13:25 by yel-bouk          #+#    #+#              #
#    Updated: 2025/01/14 12:48:46 by yel-bouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address -g3
RM = rm -f

SRCS = main.c
OBJS = $(SRCS:.c=.o)

MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx.a

# Detect OS
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	INCLUDES = -I/usr/include -Imlx
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else ifeq ($(UNAME), Darwin)
	INCLUDES = -I/opt/X11/include -Imlx
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit

endif

# Default target
all: $(MLX_LIB) $(NAME)

# Compile .c to .o
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

# Link executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

# Build MiniLibX
$(MLX_LIB):
	@make -C $(MLX_DIR)

# Clean object files
clean:
	$(RM) $(OBJS)

# Full clean
fclean: clean
	$(RM) $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
