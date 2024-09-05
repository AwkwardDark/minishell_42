# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 14:39:49 by pajimene          #+#    #+#              #
#    Updated: 2024/09/05 14:00:55 by pajimene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3 -I include -I libft/includes

# Source Files
SRC_MAIN    =  main.c

SRC_INIT    =  exit_error.c init.c
                
SRC_PARSING =  check_syntax.c tokenizer.c lexer_utils.c token_utils.c check_grammar.c redir.c

SRC_UTILS   =  lst_utils.c ft_cpyenv.c ls_env.c symbols.c

# Object files
OBJ_MAIN = $(addprefix src/, $(SRC_MAIN:.c=.o))

OBJ_INIT = $(addprefix src/init/, $(SRC_INIT:.c=.o))

OBJ_PARSING = $(addprefix src/parsing/, $(SRC_PARSING:.c=.o))

OBJ_UTILS = $(addprefix src/utils/, $(SRC_UTILS:.c=.o))

OBJ = $(OBJ_MAIN) $(OBJ_INIT) $(OBJ_PARSING) $(OBJ_UTILS)

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

# Compilation
$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lft -Llibft -Iinclude -lreadline

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
