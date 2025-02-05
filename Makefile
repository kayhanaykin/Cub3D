# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaykin <kaykin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/29 15:48:10 by kaykin            #+#    #+#              #
#    Updated: 2025/02/05 11:45:13 by kaykin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= cub3d
CC			= cc -g
FLAGS 		= -Wall -Wextra -Werror 
FLAGSA 		= -fsanitize=address
EXTRA_FLAGS = -Wno-deprecated
SRCS		= 	main.c hook.c mlx.c
OBJS		:= $(SRCS:.c=.o)

FRAMEWORKS	= -lXext -lX11 -lm -lz
AR_LIBFT	= libft/libft.a
AR_LIBMLX	= minilibx-linux/libmlx.a
DIR_LIBFT	= libft
DIR_LIBMLX	= minilibx-linux

all: $(NAME)

seg: $(OBJS) 
	make -s -C $(DIR_LIBFT)
	make -s -C $(DIR_LIBMLX) CFLAGS+="$(EXTRA_FLAGS)"
	$(CC) $(FLAGS) $(FLAGSA) $(OBJS) $(AR_LIBFT) $(AR_LIBMLX) $(FRAMEWORKS) -o $(NAME)

$(NAME): $(OBJS) 
	make -s -C $(DIR_LIBFT)
	make -s -C $(DIR_LIBMLX) CFLAGS+="$(EXTRA_FLAGS)"
	$(CC) $(FLAGS) $(OBJS) $(AR_LIBFT) $(AR_LIBMLX) $(FRAMEWORKS) -o $(NAME) -v

clean:                                                             
			rm -f $(OBJS)
			make -s -C $(DIR_LIBFT) clean

fclean: clean
			rm -f $(NAME)
			make -C $(DIR_LIBFT) fclean
			make -C $(DIR_LIBMLX) clean

clear:
	clear

re: fclean all

run1: re
			./$(NAME) ./test_maps/test.cub

run2: re
			./$(NAME) ./test_maps/square.cub

valg: re
			valgrind ./$(NAME) ./test_maps/test.cub

	
.PHONY: all clean fclean re

