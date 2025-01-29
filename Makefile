# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaykin <kayhana42istanbul@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/29 15:48:10 by kaykin            #+#    #+#              #
#    Updated: 2025/01/29 16:20:06 by kaykin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= cub3d
CC			= cc -g
FLAGS 		= -Wall -Wextra -Werror -fsanitize=address
EXTRA_FLAGS = -Wno-deprecated
SRCS		= 	main.c hook.c mlx.c
OBJS		:= $(SRCS:.c=.o)

FRAMEWORKS	= -lXext -lX11 -lm -lz
AR_LIBFT	= libft/libft.a
AR_LIBMLX	= minilibx-linux/libmlx.a
DIR_LIBFT	= libft
DIR_LIBMLX	= minilibx-linux

all: $(NAME)

$(NAME): $(OBJS) 
	make -s -C $(DIR_LIBFT)
	make -s -C $(DIR_LIBMLX) CFLAGS+="$(EXTRA_FLAGS)"
	$(CC) $(FLAGS) $(OBJS) $(AR_LIBFT) $(AR_LIBMLX) $(FRAMEWORKS) -o $(NAME)

clean:                                                             
			rm -f $(OBJS)
			make -s -C $(DIR_LIBFT) clean

fclean: clean
			rm -f $(NAME)
			make -C $(DIR_LIBFT) fclean
			make -C $(DIR_LIBMLX) clean

re: fclean all

run1: 
			./$(NAME) ./test_maps/10-2.cub

run2: 
			./$(NAME) ./test_maps/20-60.cub

	
.PHONY: all clean fclean re

