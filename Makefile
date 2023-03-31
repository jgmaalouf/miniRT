# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 16:59:04 by jmaalouf          #+#    #+#              #
#    Updated: 2023/03/31 14:36:08 by jmaalouf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLD	= \033[1m
GREEN	= \033[32;1m
RESET	= \033[0m

NAME	= miniRT
INCL	= -I include -I $(LIBMLX)/include/MLX42 -I $(LIBFT) -I $(LIBFT)/libft
CFLAGS	= -Wall -Wextra -Werror -Ofast $(INCL)
LDFLAGS = -L $(LIBFT)/ -l_extended -L $(LIBMLX)/build/ -lmlx42

VPATH	= src/ src/graphics/ src/graphics/intersection/ src/graphics/shading/ src/math/ src/parse src/parse/transformation/ src/utils/ include/

LIBMLX	= ./lib/MLX42
LIBFT	= ./lib/the_library

OS		= $(shell uname)

ifeq ($(OS), Darwin)
CFLAGS += -fsanitize=address,undefined
LDFLAGS	+= -L $(LIBMLX)/glfw_lib/ -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -fsanitize=address,undefined
endif

ifeq ($(OS), Linux)
LDFLAGS	+= -ldl -pthread -lm -lglfw -lbsd
endif

SRCS	= main.c \
			display.c \
			cylinder_plane.c cylinder.c plane.c sphere.c world.c \
			light.c pixel_color.c ray.c shading_utils.c \
			matrix.c vector_advanced.c vector_basic.c vector_length.c \
			transform_scene.c transform_vector.c transform.c \
			elem_count.c fill_scene_hittable.c fill_scene.c parse.c validate.c \
			errors.c memory_alloc.c panic.c utils.c

HEADERS	= elem_count.h errors.h graphics.h intersection.h matrix.h \
			memory_alloc.h parse.h ray.h scene.h transform.h utils.h vector.h

ODIR	= obj
OBJS	= $(addprefix $(ODIR)/,$(patsubst %.c, %.o, $(SRCS)))

all: libft libmlx $(NAME)
	@#curl -s https://themushroomkingdom.net/sounds/wav/smb/smb_world_clear.wav -o sound.wav && afplay sound.wav && rm sound.wav &
	@#-curl --fail --silent --show-error -m 7 parrot.live 2> /dev/null ; true
	@#printf "$(GREEN)$(BOLD)\tminiRT compiled successfully\n$(RESET)"
	@#say MLX compiled successfully bitch

libmlx:
	@bash setup_lib.sh

libft:
	@make -C $(LIBFT)

$(ODIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ -c $<

$(ODIR):
	mkdir $(ODIR)

$(NAME): $(ODIR) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(INCL) -o $(NAME)

clean:
	rm -rf $(ODIR)
	$(MAKE) -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all, clean, fclean, re, libmlx, libft
