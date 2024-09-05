NAME = builtins
MAIN = main.c
BUILTINS = ft_cd.c ft_echo.c ft_export.c ft_env.c ft_pwd.c ft_unset.c 
UTILS = ls_env.c ft_cpyenv.c token.c
TREE = tree.c tree_utils.c
EXEC= exec_utils.c exec.c heredoc.c redirections.c single_exec.c 
ERROR= error.c

# Define the object files for builtins and utils
UTILS_OBJS = $(addprefix src/utils/, $(UTILS:.c=.o))
BUILTINS_OBJS = $(addprefix src/builtins/, $(BUILTINS:.c=.o))
TREE_OBJS = $(addprefix src/tree/, $(TREE:.c=.o))
EXEC_OBJS = $(addprefix src/exec/, $(EXEC:.c=.o))
ERROR_OBJ= $(addprefix src/errors/, $(ERROR:.c=.o))

CC = cc 
# CFLAGS = -Werror -Wall -Wextra

all: $(NAME)

# Linking the final executable
$(NAME): $(MAIN:.c=.o) $(EXEC_OBJS)  $(TREE_OBJS) $(UTILS_OBJS) $(BUILTINS_OBJS) $(ERROR_OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(MAIN:.c=.o) $(ERROR_OBJ) $(EXEC_OBJS) $(UTILS_OBJS) $(BUILTINS_OBJS) $(TREE_OBJS) -I./include -lft -L./libft -lreadline -o $@

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -I./include -c $< -o $@

# Clean object files and libraries
clean:
	rm -f $(EXEC_OBJS) $(TREE_OBJS) $(UTILS_OBJS) $(BUILTINS_OBJS) $(MAIN:.c=.o) $(BUILTINS_OBJS) $(ERROR_OBJ)
	make clean -C libft

# Clean everything including the final executable
fclean: clean
	rm -f $(NAME)
	make fclean -C libft

# Rebuild everything from scratch
re: fclean all
