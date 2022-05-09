# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 18:12:02 by tlemma            #+#    #+#              #
#    Updated: 2021/11/22 17:03:29 by tlemma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

BONUS = so_long_bonus

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

RM = rm -f

AR = ar rs

SOURCES = ./src/so_long.c \
			./src/utils.c \
			./src/game.c \
			./src/map.c \
			./src/movements.c \
			./src/imgs.c

BOUNS_SRC = ./src/bonus/so_long_bonus.c \
			./src/utils.c \
			./src/game.c \
			./src/map.c \
			./src/movements.c \
			./src/imgs.c

OBJECTS = $(SOURCES:.c=.o)

LIBFT = $(MAKE) -C ./libft 

MLX = $(MAKE) -C ./mlx 

$(NAME):
	$(LIBFT)
	$(MLX)
	$(CC) $(CFLAGS) $(SOURCES) ./libft/libft.a -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) -I ./mlx

all: $(NAME)

bonus: 
	$(LIBFT)
	$(MLX)
	$(CC) $(CFLAGS) $(BOUNS_SRC) ./libft/libft.a -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(BONUS) -I ./mlx

clean:
	$(MAKE) -C ./libft clean
	$(MAKE) -C ./mlx clean
	$(RM) $(OBJECTS) 

fclean: clean
	$(RM) ./libft/libft.a
	$(RM) $(NAME) $(BONUS)

re: fclean all
		
.PHONY: all clean fclean re bonus .c .o