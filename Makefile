# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 17:01:46 by lubenard          #+#    #+#              #
#    Updated: 2019/05/03 22:15:46 by lubenard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = srcs/main.c \
	  srcs/get_command.c \
	  srcs/get_env.c \
	  srcs/execute_command.c \
	  srcs/get_path.c \
	  srcs/handle_signals.c \
	  srcs/save_command.c \
	  srcs/autocomplete.c \
	  srcs/multiple_command.c \
	  srcs/errors.c \
	  srcs/builtins/echo.c \
	  srcs/builtins/echo2.c \
	  srcs/builtins/print_env.c \
	  srcs/builtins/set_env.c \
	  srcs/builtins/unset_env.c \
	  srcs/builtins/cd.c \
	  srcs/builtins/cd2.c

OBJ = $(SRC:.c=.o)

CC = clang

CFLAGS = -g3 -Wall -Wextra -Werror

.SILENT:

all:  $(NAME)

$(NAME): $(OBJ)
	@cd libft && make
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJ) libft/libft.a
	@printf "\033[33mCompilation de $(NAME)...\033[0m"
	@printf "\033[32m[✓]\033[0m\n"

libft:
	@cd libft && make

%.o : %.c
	@printf "\033[36mCompilation de $<...\033[0m"
	@$(CC) -c $(CFLAGS) $< -o $@
	@printf "\033[32m[✓]\033[0m\n"

clean:
	@cd libft && make clean
	@rm -f $(OBJ)
	@printf "\033[31mclean de $(NAME)...\033[0m"
	@printf "\033[32m[✓]\033[0m\n"

fclean: clean
	@rm -f $(NAME)
	@rm -f libft/libft.a
	@printf "\033[31mFclean de srcs/libft.a...\033[0m\033[32m[✓]\033[0m\n"
	@printf "\033[31mFclean de $(NAME)...\033[0m"
	@printf "\033[32m[✓]\033[0m\n"
	@rm -rf .history

re: fclean all

.PHONY: all re fclean clean libft
