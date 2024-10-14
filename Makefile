NAME = cub3d
CC = cc 
CFLAG = -Wall -Wextra -Werror -fsanitize=address -g3

SRC = cub3d.c \
	  my_malloc.c \
	  gnl.c \
	  parce.c \
	  ft_libft.c 

OBJ = $(SRC:.c=.o)

all:$(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@



$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)



clean :
	rm -f $(OBJ)
fclean : clean
	rm -f $(NAME)

re : fclean all
