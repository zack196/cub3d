NAME=cub3d

SRC = cub3d.c libft.c mlx.c my_malloc.c player.c tmp.c 

OBJ=$(SRC:.c=.o)


all : $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

$(OBJ):cub3d.h

$(NAME): $(OBJ)
	$(CC) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean :
	rm -f $(OBJ) $(OBJ_bonus)

fclean : clean
	rm -f $(NAME) $(BONUS)

re : fclean all

.PHONY : clean