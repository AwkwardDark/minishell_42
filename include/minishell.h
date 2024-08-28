/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:21:41 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/28 15:23:49 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

extern int g_signal;

/*Error and Memory managment*/
void	ft_free_exit(t_data *data);
void	ft_free_tab(char **argv);

/*Parser, Lexer and Simple Syntax management*/
int		ft_init_data(char **envp, t_data *data);
int		ft_error_clean(t_data *data, int code);
//void	ft_parser(t_cmd *cmd);
//void	ft_check_syntax(t_cmd *cmd);
//int 	ft_quote_syntax(t_cmd *cmd);

/*Testing utils*/
void	ft_print_tab(char **tab);

#endif
