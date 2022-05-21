# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 16:08:59 by jroth             #+#    #+#              #
#    Updated: 2022/05/21 16:13:28 by tlemma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

MLX		=	./_MLX42/libmlx42.a

GLFW	=	-lglfw -L /Users/$(USER)/goinfre/.brew/opt/glfw/lib/

LIBFT	=	./libft/

SRC		=	./src/main.c ./src/parser/get_info.c ./src/parser/map.c ./src/parser/validate_map.c \
			./src/init_mlx.c ./src/movement.c  ./src/draw.c ./src/texture.c\
			./src/raycasting.c ./src/utils.c

OBJ		=	$(SRC:.c=.o)

$(NAME): $(OBJ)
	@echo 
	@make -C $(LIBFT)
	@$(CC) -g -o $(NAME) $(OBJ) $(MLX) $(GLFW) $(LIBFT)libft.a

clean:
	rm -f $(shell find ./src/* -iname "*.o")
	@make clean -C $(LIBFT)

fclean:
	rm -f cub3D
	rm -f $(LIBFT)libft.a

re: clean fclean $(NAME)

mlx:
	make -C ./_MLX42/

cleanmlx:
	make clean -C ./_MLX42/
	make fclean -C ./_MLX42/
