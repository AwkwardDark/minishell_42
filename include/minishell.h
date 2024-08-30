/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:21:41 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/30 19:22:45 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "structs.h"
# include "../libft/includes/libft.h"

/*color for the minishell prompt*/
# define GREEN "\033[0;92m"
# define GRAS "\033[1m"
# define RESET "\033[0m"

/*Message error macros*/
# define SYNTAX_ERR_Q "There's a quote syntax error\n"
# define SYNTAX_ERR_B "There's a bracket syntax error\n"

/*Character macros*/
# define S_QUOTE '\''
# define D_QUOTE '\"'
# define SPACE ' '
# define TAB '\t'
# define O_PAR '('
# define C_PAR ')'
# define PIPE '|'
# define I_REDIR '<'
# define O_REDIR '>'
# define HEREDOC "<<"
# define APPEND ">>"
# define AND "&&"
# define OR "||"

extern int g_signal;

/*Error and Memory managment*/
void	ft_free_exit(t_data *data);

/*Double Linked List utils*/
void	ft_free_lst(t_token **a);
t_token	*ft_lstnew(char *content);
t_token	*ft_lstlast(t_token *lst);
void	ft_lstadd_back(t_token **lst, t_token *new);
void 	ft_print_lst(t_token *lst);

/*Env List*/
t_env	*ft_initenv(char *key, char *value);
void	ft_addlstenv(t_env **env, char *key, char *value);
void	ft_clrenv(t_env **head);
void	ft_clrenvnode(t_env *env);
t_env	*ft_cpyenv(char **env);

/*Parser, Lexer and Simple Syntax management*/
int		ft_init_data(char **envp, t_data *data);
void	ft_error(int code);
void	ft_parser(char *input, t_data *data);
void	ft_tokenize(char *input, t_data *data);
int 	ft_quote_syntax(char *input);

/*Parsing Utils*/
int		is_quote(char c, t_data *data);
int 	is_special(char *input, int *i);

/*Testing utils*/
void 	ft_print_lst(t_token *lst);

#endif
