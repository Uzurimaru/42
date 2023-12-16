# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 13:31:22 by rwintgen          #+#    #+#              #
#    Updated: 2023/12/13 15:06:23 by rwintgen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= fdf
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -O0 -g
LIBMLX	:= ./MLX42
LIBFT	:= ./libft
LIBFTA	:= $(LIBFT)/libft.a

HEADERS	:= -I ./includes -I $(LIBMLX)/include -I $(LIBFT)
LIBS	:= $(LIBFTA) $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm 
SRCS	:= $(shell find ./sources -iname "*.c")
OBJS	:= ${SRCS:.c=.o}

all: libft libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	cd $(LIBFT) && make 

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@cd $(LIBFT) && make clean

fclean: clean
	@rm -rf $(NAME)
	@rm -r $(LIBFTA)

re: clean all
