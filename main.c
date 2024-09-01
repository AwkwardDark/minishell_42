/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 22:21:37 by pierre            #+#    #+#             */
/*   Updated: 2024/09/01 23:11:33 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_data	*data;
	char *input;

	argv = argv;
	argc = argc + 1;
	// data = (t_data *)malloc(sizeof(t_data));
	// data->env = ft_cpyenv(env);
	// while((input = readline("prompt> ")) != 0) 
	// {
	// 	if (!ft_strcmp(input, "exit"))
	// 		break ;
	// 	else if (!ft_strncmp(input, "cd ", 2))
	// 		ft_cd(&input[2]);
	// 	else if (!ft_strncmp(input, "pwd", 3))
	// 		ft_pwd();
	// 	else if (!ft_strcmp(input, "env"))
	// 		ft_env(data->env);
	// 	else if (!ft_strncmp(input, "unset", 5))
	// 	{
	// 		if (input[5]) {
	// 			ft_unset(&input[6], data);

	// 		}
	// 	}
	// 	else if(!ft_strncmp(input, "export", 6))
	// 	{
	// 		char *key = (char *)malloc(sizeof(char) * 4);
	// 		key[0]='N';
	// 		key[1]='E';
	// 		key[2]='W';
	// 		key[3]='\0';
	// 		char *val = (char *)malloc(sizeof(char) * 5);
	// 		val[0]='Z';
	// 		val[1]='I';
	// 		val[2]='Z';
	// 		val[3]='I';
	// 		val[4]='\0';
	// 		ft_export(&data->env, key, val);
	// 	}
	// 	else if (!ft_strcmp(input, "echo"))
	// 	{
	// 		printf("**********************\n");
	// 		char *tab[5] = {"hello", "world", "I", "love", 0};
	// 		ft_echo(tab, 1);
	// 		printf("**********************\n");
	// 		ft_echo(tab, 0);
	// 		char *tab2[2] = {"hello", 0};
	// 		printf("**********************\n");
	// 		ft_echo(tab2, 0);
	// 		printf("**********************\n");
	// 		printf("**********************\n");
	// 		ft_echo(tab2, 1);
	// 	}
	// 	free(input);
	// }
	// free(input);

	t_token	*token = ft_lstnew("ls", CMD);
	t_token	*tokencmd2 = ft_lstnew("ls", CMD);
	t_token	*tokencmd3 = ft_lstnew("echo 'hello'", CMD);
	t_token *tokencmd4 = ft_lstnew("wc -l", CMD);

	t_token *PO = ft_lstnew("(", O_PAR);
	t_token *PF = ft_lstnew(")", C_PAR);

	t_token *tokenOR = ft_lstnew("||", OR);
	t_token *tokenOR2 = ft_lstnew("||", OR);
	t_token *tokenAND = ft_lstnew("&&", AND);

	ft_lstadd_back(&token, tokenOR);
	ft_lstadd_back(&token, tokencmd2);
	ft_lstadd_back(&token, tokenAND);
	ft_lstadd_back(&token, PO);
	ft_lstadd_back(&token, tokencmd3);
	ft_lstadd_back(&token, tokenOR2);
	ft_lstadd_back(&token, tokencmd4);
	ft_lstadd_back(&token, PF);

	t_btree *tree_tokens = create_tokentree(&token);
	display_btree(tree_tokens);
	
	return (0);;
}
