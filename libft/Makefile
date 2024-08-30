LIBFT = ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memset.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c \
	ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
	 ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
	ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_memdel.c ft_strnew.c ft_strdel.c \
	ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strlcpy.c \
	ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_atoi_base.c ft_strndup.c \
	ft_atof.c ft_pow.c clear_wordarr.c
GNL = get_next_line_bonus.c get_next_line_utils_bonus.c
PRT = ft_flags.c ft_formats.c ft_printf.c ft_utils.c
BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c 
ALL_SRC = $(LIBFT) $(PRT) $(GNL) $(BONUS)
OBJS = $(addprefix src/, $(ALL_SRC:.c=.o))
NAME = libft.a
ARC = ar
OPT = -rcs
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(ARC) $(OPT) $(NAME) $^

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
