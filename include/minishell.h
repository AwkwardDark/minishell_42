/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:40:22 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/01 11:59:21 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"

/* src/utils/ls_env.c */
t_env	*ft_initenv(char *key, char *value);
void	ft_addlstenv(t_env **env, char *key, char *value);
void	ft_clrenv(t_env **head);
void	ft_clrenvnode(t_env *env);

/* src/utils/ft_cpyenv.c */
t_env	*ft_cpyenv(char **env);

/* src/utils/token.c */
void	ft_free_lst(t_token **a);
t_token	*ft_lstnew(char *content, t_type type);
t_token	*ft_lstlast(t_token *lst);
void	ft_lstadd_back(t_token **lst, t_token *new);
void	ft_print_lst(t_token *lst);
void	display_type(t_type type);

/* src/tree/tree.c */
t_btree	*init_tree(t_token *token, t_btree *left, t_btree *right);
static t_token	*contains_priority(t_token *token, int priority);
t_token	*get_endlst(t_token *token);
t_btree	*create_tokentree(t_token **token);
void	display_tree(t_btree *tree);

/* src/builtins */
void	ft_cd(char *path);
void	ft_pwd(void);
void	ft_env(t_env *env);
void	ft_unset(char *var, t_data *data);
void	ft_export(t_env **env, char *key, char *value);
void	ft_echo(char **str, int NFLAG);

#endif