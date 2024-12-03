EXEC_DIR        =   src/parsing/
INIT_DIR		=	src/init/
RAY_CASTING		=	src/display_game/
CFLAGS          =   -Wall -Wextra -Werror
NAME            =   cub3d
BONUS 			=	cub3d_bonus
LIBFT_DIR       =   libft
LIBFT           =   $(LIBFT_DIR)/libft.a
CC              =   cc
F_LFT           =   -L$(LIBFT_DIR) -lft
INC             =   -I$(LIBFT_DIR) -Iinclude
INCLUDE         =   include/cub3d.h

SRC             =   main.c \
                    $(EXEC_DIR)pars_file.c \
                    $(EXEC_DIR)pars_map.c \
                    $(EXEC_DIR)add_data.c \
                    $(EXEC_DIR)check_texture_colors.c \
                    $(EXEC_DIR)my_malloc.c \
                    $(EXEC_DIR)pars_walls.c \
                    $(EXEC_DIR)parsing_cub.c \
                    $(EXEC_DIR)parsing_utils.c \
					$(INIT_DIR)init.c \
					$(RAY_CASTING)render.c \
					$(RAY_CASTING)events.c \
					$(RAY_CASTING)utiles.c \
					$(RAY_CASTING)ray.c \
					$(RAY_CASTING)tex.c 



SRC_BONUS		=	bonus/main_bonus.c \
					bonus/parsing/pars_file_bonus.c \
					bonus/parsing/pars_map_bonus.c \
					bonus/parsing/add_data_bonus.c \
					bonus/parsing/check_texture_colors_bonus.c \
					bonus/parsing/my_malloc_bonus.c \
					bonus/parsing/pars_walls_bonus.c \
					bonus/parsing/parsing_cub_bonus.c \
					bonus/parsing/parsing_utils_bonus.c \
					bonus/init/init_bonus.c \
					bonus/display_game/render_bonus.c \
					bonus/display_game/events_bonus.c \
					bonus/display_game/utiles_bonus.c \
					bonus/display_game/ray_bonus.c \
					bonus/display_game/tex_bonus.c \
					bonus/display_game/mini_map_bonus.c \
					bonus/display_game/sprite_bonus.c \
					bonus/display_game/math_utiles_bonus.c \
					bonus/display_game/mouse_move_bonus.c


OBJ             =   $(SRC:.c=.o)
OBJ_BONUS		=	$(SRC_BONUS:.c=.o)

all: $(LIBFT) $(NAME)

bonus: $(LIBFT) $(BONUS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ) : $(INCLUDE)

$(OBJ_BONUS) : bonus/cub3d_bonus.h

%.o: %.c 
	$(CC) $(CFLAGS) $(INC) -Imlx -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(F_LFT) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(BONUS): $(OBJ_BONUS)
	$(CC) $(OBJ_BONUS) $(F_LFT) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit -o $(BONUS)

#lunix
# %.o: %.c
# 	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

# $(NAME): $(OBJ)
# 	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)


clean:
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJ_BONUS)
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(BONUS)
	@rm -f $(NAME)

re: fclean all

ree : fclean bonus

.PHONY: all clean fclean re $(LIBFT)
