/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 22:21:37 by pierre            #+#    #+#             */
/*   Updated: 2024/09/05 15:12:30 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 int main(int argc, char **argv, char **env)
{
/*  	t_data	*data;
	char *input;

	argv = argv;
	argc = argc + 1;
	data = (t_data *)malloc(sizeof(t_data)); 
	data->env = ft_cpyenv(env);*/
/*	char **format_env = lstenv_towordarr(data->env);
	int i = 0;
 */
	
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

	// test on the binary tree generation
/* 	t_token	*token = ft_lstnew("ls", CMD);
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
	ft_lstadd_back(&token, PF); */

/* 	t_token *token = ft_lstnew("cmd1", WORD);
	t_token *tokencmd2 = ft_lstnew("cmd2", CMD);
	t_token *tokencmd3 = ft_lstnew("cmd3", CMD);
	t_token *tokencmd4 = ft_lstnew("cmd4", CMD);
	t_token *tokencmd5 = ft_lstnew("cmd5", CMD);
	t_token *tokencmd6 = ft_lstnew("cmd6", CMD);
	t_token *tokencmd7 = ft_lstnew("cmd7", CMD);

	t_token	*tokenpipe1 = ft_lstnew("|", PIPE);
	t_token	*tokenpipe2 = ft_lstnew("|", PIPE);

	t_token	*tokenOP = ft_lstnew("(", O_PAR);
	t_token	*tokenCP = ft_lstnew(")", C_PAR);

	t_token	*tokenAND1 = ft_lstnew("&&", AND);
	t_token	*tokenAND2 = ft_lstnew("&&", AND);
	t_token	*tokenAND3 = ft_lstnew("&&", AND);

	t_token	*tokenOR = ft_lstnew("||", OR);

	ft_lstadd_back(&token, tokenpipe1);
	ft_lstadd_back(&token, tokencmd2);
	ft_lstadd_back(&token, tokenpipe2);
	ft_lstadd_back(&token, tokencmd3);
	ft_lstadd_back(&token, tokenAND1);
	ft_lstadd_back(&token, tokencmd4);
	ft_lstadd_back(&token, tokenOR);
	ft_lstadd_back(&token, tokenOP);
	ft_lstadd_back(&token, tokencmd5);
	ft_lstadd_back(&token, tokenAND2);
	ft_lstadd_back(&token, tokencmd6);
	ft_lstadd_back(&token, tokenCP);
	ft_lstadd_back(&token, tokenAND3);
	ft_lstadd_back(&token, tokencmd7); */

	t_env *env_lst = ft_cpyenv(env);
	t_token *token = ft_lstnew("ls", WORD);
	t_token *token2 = ft_lstnew("-l", WORD);
	t_token *tokenpipe = ft_lstnew("|", PIPE);
	t_token *token3 = ft_lstnew("wc", WORD);
	t_token *token4 = ft_lstnew("-l", WORD);
	t_token *tokenand = ft_lstnew("&&", AND);
	t_token *token5 = ft_lstnew("ls", WORD);

	ft_lstadd_back(&token, token2);
	ft_lstadd_back(&token, tokenpipe);
	ft_lstadd_back(&token, token3);
	ft_lstadd_back(&token, token4);
	ft_lstadd_back(&token, tokenand);
	ft_lstadd_back(&token, token5);
	// ft_lstadd_back(&token, token6);

	// ft_print_lst(token);
	t_btree *tree_tokens = create_tokentree(&token); 
	// display_btree(tree_tokens);
	int ret = exec_btree(tree_tokens, env_lst);
	printf("exit status: %d\n", ret);
	// display_btree(tree_tokens);
	ft_clrenv(&env_lst);
	clr_btree(tree_tokens);
	return (0);;
}

/* int	main(int argc, char **argv, char **env)
{
	argc = 0;
	argv = 0;
	int	i = 0;

	char	*tab[3] = {"ls", "-l", 0};
	char	*file[3] = {"file1", "file2", 0};
	int child = fork();
	int	fd;
	if (child == 0)
	{
		while (file[i])
		{
			fd = open(file[i], O_CREAT | O_TRUNC | O_WRONLY, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			i++;
		}
		execve("/usr/bin/ls", tab, env);
	}
	return (0);
} */