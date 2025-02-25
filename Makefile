NAME 		= cub3d
CC			= cc
FLAGS 		= -Wall -Wextra -Werror 
FLAGSA 		= -fsanitize=address -g
EXTRA_FLAGS = -Wno-deprecated
SRCS		= check.c  color.c  create.c  flood_fill.c  flood_fill_utils.c  \
				hook.c  main.c  main_utils.c  parser_map.c  parser_meta.c  \
				raycaster.c  raycaster_utils.c
OBJS		:= $(SRCS:.c=.o)

FRAMEWORKS	= -lXext -lX11 -lm
AR_LIBFT	= libft/libft.a
AR_LIBMLX	= minilibx-linux/libmlx.a
DIR_LIBFT	= libft
DIR_LIBMLX	= minilibx-linux

all: $(NAME)

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

run1: $(OBJS)
			./$(NAME) ./test_maps/test.cub

run2: $(OBJS)
			./$(NAME) ./test_maps/square.cub

run3: $(OBJS)
			./$(NAME) ./test_maps/pdf_big.cub

valg: re
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
			./$(NAME) ./test_maps/test.cub

seg: $(OBJS)
	$(CC) $(FLAGS) $(FLAGSA) $(OBJS) $(AR_LIBFT) $(AR_LIBMLX) $(FRAMEWORKS) -o $(NAME)
	./$(NAME) ./test_maps/test.cub

.PHONY: all clean fclean re

