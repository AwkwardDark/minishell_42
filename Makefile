NAME = minishell
MAIN = main.c
BUILTINS = ft_cd.c ft_echo.c ft_export.c ft_env.c ft_pwd.c ft_unset.c exec_builtin.c ft_is_builtins.c ft_exit.c
UTILS = ls_env.c lst_utils_1.c lst_utils_2.c symbols.c ft_cpyenv.c exec_utils1.c exec_utils2.c free_exec.c exit_utils.c export_parse.c write_utils.c is_directory.c redirections_utils.c exit_success.c
TREE = tree.c tree_utils.c
EXEC= exec_utils.c exec.c heredoc.c heredoc_utils.c redirections.c redirections_utils.c single_exec.c exec_operators.c wait.c expand.c expand_utils.c wildcard.c
ERROR= error.c builtins_errors.c
SIGNAL= mainp_handler.c childp_handler.c
GB= clr_gb.c gb_utils.c

# Pablo
SRC_INIT    =  init.c
SRC_PARSING =  check_syntax.c tokenizer.c lexer_utils.c token_utils.c check_grammar.c redir.c quotes.c pre_expand.c pre_wildcard.c

# Object files Pablo
OBJ_INIT = $(addprefix src/init/, $(SRC_INIT:.c=.o))
OBJ_PARSING = $(addprefix src/parsing/, $(SRC_PARSING:.c=.o))

# Define the object files for builtins and utils
UTILS_OBJS = $(addprefix src/utils/, $(UTILS:.c=.o))
BUILTINS_OBJS = $(addprefix src/builtins/, $(BUILTINS:.c=.o))
TREE_OBJS = $(addprefix src/tree/, $(TREE:.c=.o))
EXEC_OBJS = $(addprefix src/exec/, $(EXEC:.c=.o))
ERROR_OBJ= $(addprefix src/errors/, $(ERROR:.c=.o))
SIGNAL_OBJ = $(addprefix src/signals/, $(SIGNAL:.c=.o))
OBJ_GB = $(addprefix src/gb_collector/, $(GB:.c=.o))

CC = cc 
CFLAGS = -Werror -Wall -Wextra -g3 #-fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fsanitize=null -fsanitize=return

all: $(NAME)

# Linking the final executable
$(NAME): $(MAIN:.c=.o) $(EXEC_OBJS)  $(TREE_OBJS) $(UTILS_OBJS) $(BUILTINS_OBJS) $(ERROR_OBJ) $(OBJ_INIT) $(OBJ_PARSING) $(SIGNAL_OBJ) $(OBJ_GB)
	make -C libft
	$(CC) $(CFLAGS) $(MAIN:.c=.o) $(OBJ_GB) $(OBJ_INIT) $(OBJ_PARSING) $(ERROR_OBJ) $(EXEC_OBJS) $(UTILS_OBJS) $(BUILTINS_OBJS) $(TREE_OBJS) $(SIGNAL_OBJ) -I./include -lft -L./libft -lreadline -o $@

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -I./include -c $< -o $@

# Clean object files and libraries
clean:
	rm -f $(EXEC_OBJS) $(OBJ_GB) $(TREE_OBJS) $(UTILS_OBJS) $(BUILTINS_OBJS) $(MAIN:.c=.o) $(BUILTINS_OBJS) $(ERROR_OBJ) $(OBJ_INIT) $(OBJ_PARSING) $(SIGNAL_OBJ)
	make clean -C libft

# Clean everything including the final executable
fclean: clean
	rm -f $(NAME)
	make fclean -C libft

# Rebuild everything from scratch
re: fclean all
