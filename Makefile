# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jroth <jroth@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 16:08:59 by jroth             #+#    #+#              #
#    Updated: 2022/05/18 14:58:41 by jroth            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

MLX		=	./_MLX42/libmlx42.a

GLFW	=	-lglfw -L /Users/$(USER)/.brew/opt/glfw/lib/

LIBFT	=	./inc/libft/

SRC		=	$(shell find ./src/* -iname "*.c")

OBJ		=	$(SRC:.c=.o)

$(NAME): $(OBJ)
	make -C $(LIBFT)
	$(CC) -g -o $(NAME) $(OBJ) $(MLX) $(GLFW) $(LIBFT)libft.a
	make clean

clean:
	rm -f $(shell find ./src/* -iname "*.o")

fclean:
	rm -f cub3D

re: clean fclean $(NAME)

mlx:
	make -C ./_MLX42/

cleanmlx:
	make clean -C ./_MLX42/
	make fclean -C ./_MLX42/
