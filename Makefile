#------------MakeFile------------#
NAME = fdf

CC = gcc
CFLAGS = -Wall -Wextra -Werror 

#-fsanitize=address

SRCS_DIR = ./src/
SRCS =  fdf.c\
		draw.c\
		main.c\
		parse.c

OBJS_DIR = ./obj/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

UNAME_S := $(shell uname -s)

MLXPATH = MLX42/libmlx42.a
LIBFTPATH = 42-libft/libft.a
LIBS = MLX42/libmlx42.a -ldl -lglfw -lm -L /opt/homebrew/opt/glfw/lib
#Mac_42#
#	MLX42/libmlx42.a -ldl -lglfw -lm -L /Users/${USER}/.brew/opt/glfw/lib/
#Mac_ventura#
#	 MLX42/libmlx42.a -ldl -lglfw -lm -L /opt/homebrew/opt/glfw/lib

all: obj $(NAME)

obj:
	mkdir obj

$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
	$(CC) $(CFLAGS) -I ./includes/ -I ./42-libft/ -o $@ -c $< -g

$(MLXPATH):
	make -C MLX42/

$(LIBFTPATH):
	make -C 42-libft/

$(NAME): $(OBJS)  $(MLXPATH)  $(LIBFTPATH)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -L ./42-libft/ -l ft -o $(NAME) -g

 #ft ./memory-leaks/memory_leaks.a

clean:
	make fclean -C 42-libft/
	rm -rf obj $(NAME)

fclean: clean
	make fclean -C MLX42/
#	rm -rf MLX42/build/

r: all
	./$(NAME) test_maps/elem2.fdf

re: fclean all

.PHONY: all clean fclean re r