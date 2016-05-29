# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 11:09:29 by amathias          #+#    #+#              #
#    Updated: 2016/05/29 16:21:37 by amathias         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INC = /

SRC =	main.c			\
		get_inter.c		\
		get_primary.c	\
		mat_eval.c		\
		shade.c			\
		raytrace.c		\
		shadow.c		\
		inter_utils.c	\
		cl_utils.c		\
		hook.c			\
		vec_calc.c		\
		vec_calc2.c		\
		free_cam.c		\
		move.c			\
		parser.c		\
		get_shape.c		\
		get_scene.c		\
		get_tools.c		\
		bitmap_writer.c	\
		color.c			\
		free_scene.c	\
		signal_fct.c	\
		gtk_build.c		\
		gtk_button.c	\
		gtk_callback.c	\
		gtk_conect_interface.c	\
		

OBJ = $(SRC:.c=.o)
NAME = rt
CC = gcc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -O3 `pkg-config --cflags gtk+-3.0`

LIB_PATH = ./libft/ /usr/local/lib/
LIB_NAME = -lft -lmlx -framework OpenCL -framework OpenGL -framework AppKit -lpthread
LIB = $(addprefix -L,$(LIB_PATH)) `pkg-config --libs gtk+-3.0`
LFLAGS = $(LIB) $(LIB_NAME)

INC_PATH = ./libft/ /usr/local/include/ /usr/X11/lib
INC = $(addprefix -I,$(INC_PATH))

all: lib $(NAME)

lib:
	@make -C ./libft

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -o $@
	@ echo "$(NAME): \033[36mcreating\033[0m  binary"

%.o: %.c
	@$(CC) $(INC) -o $@ -c $^ $(CFLAGS)
	@ echo "$(NAME): \033[34mcompiling\033[0m $<"

clean:
	@$(RM) $(OBJ)
	@make clean -C ./libft
	@ echo "$(NAME): \033[33mremoving\033[0m  objects"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C ./libft
	@ echo "$(NAME): \033[33mremoving\033[0m  binary"

re: fclean all
