# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emontagn <emontagn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 11:09:29 by amathias          #+#    #+#              #
#    Updated: 2016/07/16 11:25:58 by apaget           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INC = /

SRC =	main.c				\
		get_inter.c			\
		get_primary.c		\
		mat_eval.c			\
		gtk_build_bar.c		\
		shade.c				\
		world_conf.c		\
		perlin2.c			\
		gtk_build_menu.c	\
		gtk_call_bar.c		\
		init_value.c		\
		gtk_call_mouse.c	\
		raytrace.c			\
		rotate_obj.c		\
		shadow.c			\
		inter_utils.c		\
		cl_utils.c			\
		hook.c				\
		vec_calc.c			\
		vec_calc2.c			\
		free_cam.c			\
		move.c				\
		parser.c			\
		get_shape.c			\
		get_scene.c			\
		get_tools.c			\
		bitmap_writer.c		\
		color.c				\
		free_scene.c		\
		signal_fct.c		\
		texture_loading.c	\
		texturing.c			\
		texturing_utils.c	\
		bump_utils.c		\
		bump_mapping.c		\
		gtk_build.c			\
		gtk_button.c		\
		gtk_callback.c		\
		gtk_connect.c		\
		

OBJ = $(SRC:.c=.o)
NAME = rt
CC = gcc
RM = rm -f
CFLAGS = -g -Wall -Werror -Wextra  `pkg-config --cflags gtk+-3.0`

LIB_PATH = ./libft/
LIB_NAME = -lft -framework OpenCL -framework OpenGL -framework AppKit -lpthread
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
