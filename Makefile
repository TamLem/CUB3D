# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jroth <jroth@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 16:08:59 by jroth             #+#    #+#              #
#    Updated: 2022/05/09 17:51:45 by jroth            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

MLX =	-L ./_MLX42/ -lmlx -framework OpenGL -framework AppKit

LIBFT =	./inc/libft/

PRSR =	./src/parser/

SRC	=	./src/main.c \
		$(PRSR)map.c $(PRSR)validate_map.c

OBJ =	$(SRC:.c=.o)

$(NAME): $(OBJ)
	make -C $(LIBFT)
	$(CC) $(MLX) -o $(NAME) $(OBJ) $(LIBFT)libft.a
	
clean:
	rm -f */*/*.o
	rm -f */*.o

fclean:
	rm -f cub3D

re: clean fclean $(NAME)

mlx:
	make -C ./_MLX42/

cleanmlx:
	make clean -C ./_MLX42/
	make fclean -C ./_MLX42/