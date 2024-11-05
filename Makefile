NAME=cub3d

CC=cc 

CFLAG= -Wall -Wextra -Werror -fsanitize=address -g3 

SRC = main.c libft.c my_malloc.c render.c rays.c \
	  map.c player.c utiles.c events.c

OBJ=$(SRC:.c=.o)


all:$(NAME)

$(OBJ) : cub3d.h


# %.o: %.c
# 	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

# $(NAME): $(OBJ)
# 	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	$(CC) $(CFLAG) -Imlx -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAG) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

re : fclean all

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

.PHONY : clean