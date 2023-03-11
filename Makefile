# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amorvai <amorvai@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 16:59:04 by jmaalouf          #+#    #+#              #
#    Updated: 2023/03/11 20:35:36 by amorvai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT
VPATH	= src src/graphics src/math src/parse src/utils src/debug
HEADERS	= -I ./include -I $(LIBMLX)/include/MLX42 -I $(LIBFT)
CFLAGS	= -Wall -Wextra -Werror -O3
LIBMLX	= ./lib/MLX42
LIBFT	= ./lib/the_library
UNAME	= $(shell uname)

ifeq ($(UNAME), Darwin)
LIBS	= $(LIBMLX)/glfw_lib/libglfw3.a $(LIBMLX)/build/libmlx42.a \
			$(LIBFT)/lib_extended.a -framework Cocoa -framework OpenGL -framework IOKit
endif

ifeq ($(UNAME), Linux)
LIBS	= $(LIBMLX)/build/libmlx42.a $(LIBFT)/lib_extended.a -ldl -lglfw -pthread -lm
endif

SRCS	= main.c \
			color.c display.c \
			vector1.c vector2.c vector3.c ray.c \
			parse.c populate1.c populate2.c validate1.c validate2.c elem_count.c \
			errors.c \
			print_scene.c

OBJS	= $(addprefix obj/,$(patsubst %.c, %.o, $(SRCS)))

BOLD	= \033[1m
GREEN	= \033[32;1m
RESET	= \033[0m

all: libmlx libft $(NAME)
	# @curl -s https://themushroomkingdom.net/sounds/wav/smb/smb_world_clear.wav -o sound.wav && afplay sound.wav && rm sound.wav &
	# @-curl --fail --silent --show-error -m 7 parrot.live 2> /dev/null ; true
	# @printf "$(GREEN)$(BOLD)\tminiRT compiled successfully\n$(RESET)"
	# @say MLX compiled successfully bitch

libmlx:
	@bash setup_lib.sh

libft:
	@$(MAKE) -C $(LIBFT)

obj/%.o: %.c | obj
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "$(GREEN)$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

obj:
	@mkdir obj

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf obj
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft
