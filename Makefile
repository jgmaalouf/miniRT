
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 16:59:04 by jmaalouf          #+#    #+#              #
#    Updated: 2023/02/04 14:53:07 by jmaalouf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= mlx_test
VPATH	= src
HEADERS	= -I ./include -I $(LIBMLX)/include -I $(LIBFT)
CFLAGS	= -Wall -Wextra -Werror -O3
LIBMLX	= ./lib/MLX42
LIBFT	= ./lib/the_library
UNAME	= $(shell uname)

ifeq ($(UNAME), Darwin)
LIBS	= $(LIBMLX)/glfw_lib/libglfw3.a $(LIBMLX)/build/libmlx42.a \
			$(LIBFT)/lib_extended.a -framework Cocoa -framework OpenGL -framework IOKit
endif

SRCS	= main.c scene.c validation.c vector.c debug_und_test.c
OBJS	= $(addprefix obj/,$(SRCS:.c=.o))

BOLD	= \033[1m
GREEN	= \033[32;1m
RESET	= \033[0m

all: libmlx libft $(NAME)
	# @curl -s https://themushroomkingdom.net/sounds/wav/smb/smb_world_clear.wav -o sound.wav && afplay sound.wav && rm sound.wav &
	# @-curl --fail --silent --show-error -m 7 parrot.live 2> /dev/null ; true
	# @printf "$(GREEN)$(BOLD)\tminiRT compiled successfully\n$(RESET)"
	# @say MLX compiled successfully bitch

libmlx:
	@if [ -d ./lib/MLX42 ]; \
	then echo "\033[1;33m./lib/MLX42/ Exists\033[0m"; \
	else \
	git clone https://github.com/codam-coding-college/MLX42.git && \
	mv MLX42 ./lib && \
	curl -LO https://github.com/glfw/glfw/releases/download/3.3.8/glfw-3.3.8.bin.MACOS.zip && \
	unzip glfw-3.3.8.bin.MACOS.zip && \
	rm glfw-3.3.8.bin.MACOS.zip && \
	mv glfw-3.3.8.bin.MACOS/lib-universal glfw-3.3.8.bin.MACOS/glfw_lib && \
	mv glfw-3.3.8.bin.MACOS/glfw_lib ./lib/MLX42/ && \
	rm -rf glfw-3.3.8.bin.MACOS && \
	cd lib/MLX42 && \
	cmake -B build && \
	cmake --build build -j4; \
	fi

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
