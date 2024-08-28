# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 14:39:49 by pajimene          #+#    #+#              #
#    Updated: 2024/08/28 16:03:11 by pajimene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I include -I libft/includes

# Source Files
SRCS_MAIN = src/main.c

SRCS_INIT =		src/init/exit_error.c \
				src/init/init.c
				
SRCS_PARSING =	src/parsing/check_syntax.c \
				src/parsing/parser.c
				
SRCS_UTILS_TESTING = src/utils_testing/utils.c

# Libft source files
LIBFT_SRCS = \
	libft/src/clear_wordarr.c \
	libft/src/ft_atof.c \
	libft/src/ft_atoi_base.c \
	libft/src/ft_atoi.c \
	libft/src/ft_bzero.c \
	libft/src/ft_calloc.c \
	libft/src/ft_flags.c \
	libft/src/ft_formats.c \
	libft/src/ft_isalnum.c \
	libft/src/ft_isalpha.c \
	libft/src/ft_isascii.c \
	libft/src/ft_isdigit.c \
	libft/src/ft_isprint.c \
	libft/src/ft_itoa.c \
	libft/src/ft_lstadd_back_bonus.c \
	libft/src/ft_lstadd_front_bonus.c \
	libft/src/ft_lstclear_bonus.c \
	libft/src/ft_lstdelone_bonus.c \
	libft/src/ft_lstiter_bonus.c \
	libft/src/ft_lstlast_bonus.c \
	libft/src/ft_lstmap_bonus.c \
	libft/src/ft_lstnew_bonus.c \
	libft/src/ft_lstsize_bonus.c \
	libft/src/ft_memccpy.c \
	libft/src/ft_memchr.c \
	libft/src/ft_memcmp.c \
	libft/src/ft_memcpy.c \
	libft/src/ft_memdel.c \
	libft/src/ft_memmove.c \
	libft/src/ft_memset.c \
	libft/src/ft_pow.c \
	libft/src/ft_printf.c \
	libft/src/ft_putchar_fd.c \
	libft/src/ft_putendl_fd.c \
	libft/src/ft_putnbr_fd.c \
	libft/src/ft_putstr_fd.c \
	libft/src/ft_split.c \
	libft/src/ft_strcat.c \
	libft/src/ft_strchr.c \
	libft/src/ft_strclr.c \
	libft/src/ft_strcmp.c \
	libft/src/ft_strcpy.c \
	libft/src/ft_strdel.c \
	libft/src/ft_strdup.c \
	libft/src/ft_strequ.c \
	libft/src/ft_striter.c \
	libft/src/ft_striteri.c \
	libft/src/ft_strjoin.c \
	libft/src/ft_strlcat.c \
	libft/src/ft_strlcpy.c \
	libft/src/ft_strlen.c \
	libft/src/ft_strmap.c \
	libft/src/ft_strmapi.c \
	libft/src/ft_strncat.c \
	libft/src/ft_strncmp.c \
	libft/src/ft_strncpy.c \
	libft/src/ft_strnew.c \
	libft/src/ft_strnstr.c \
	libft/src/ft_strrchr.c \
	libft/src/ft_strstr.c \
	libft/src/ft_strtrim.c \
	libft/src/ft_substr.c \
	libft/src/ft_tolower.c \
	libft/src/ft_toupper.c \
	libft/src/ft_utils.c \
	libft/src/get_next_line_bonus.c \
	libft/src/get_next_line_utils_bonus.c

# Object files
OBJS_MAIN = $(SRCS_MAIN:.c=.o)

OBJS_INIT = $(SRCS_INIT:.c=.o)

OBJS_PARSING = $(SRCS_PARSING:.c=.o)

OBJS_UTILS_TESTING = $(SRCS_UTILS_TESTING:.c=.o)

OBJS_LIBFT = $(LIBFT_SRCS:.c=.o)

OBJS = $(OBJS_MAIN) $(OBJS_INIT) $(OBJS_PARSING) $(OBJS_UTILS_TESTING)

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

#Compilation
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_LIBFT)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re