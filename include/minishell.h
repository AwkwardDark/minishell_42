/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:40:22 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/08/30 18:41:25 by pbeyloun         ###   ########.fr       */
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

/* src/utils/ls_env.c */
t_env	*ft_cpyenv(char **env);

/* src/utils/ls_env.c */
void	ft_free_lst(t_token **a);
t_token	*ft_lstnew(char *content, t_type type);
t_token	*ft_lstlast(t_token *lst);
void	ft_lstadd_back(t_token **lst, t_token *new);
void ft_print_lst(t_token *lst);


/* src/builtins */
void	ft_cd(char *path);
void	ft_pwd(void);
void	ft_env(t_env *env);
void	ft_unset(char *var, t_data *data);
void	ft_export(t_env **env, char *key, char *value);
void	ft_echo(char **str, int NFLAG);

#endif