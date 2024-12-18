# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaykin <kayhana42istanbul@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/18 12:32:31 by kaykin            #+#    #+#              #
#    Updated: 2024/12/18 12:37:20 by kaykin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= cub3d
CC			= gcc -g
FLAGS 		= -Wall -Wextra -Werror
EXTRA_FLAGS = -Wno-deprecated
SRCS		= 	main.c draw_mesh.c draw_transforms.c hook.c utils.c
OBJS		:= $(SRCS:.c=.o)

FRAMEWORKS	= -framework OpenGL -framework AppKit
AR_LIBFT	= libft/libft.a
AR_LIBMLX	= minilibx_linux/libmlx.a
DIR_LIBFT	= libft
DIR_LIBMLX	= minilibx_linux

all: $(NAME)
	rm -rf minilibx-linux.tgz

$(NAME): $(OBJS) 
	make -s -C $(DIR_LIBFT)
	make -s -C $(DIR_LIBMLX) CFLAGS+="$(EXTRA_FLAGS)"
	$(CC) $(FLAGS) $(OBJS) $(AR_LIBFT) $(AR_LIBMLX) $(FRAMEWORKS) -o $(NAME) -g

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