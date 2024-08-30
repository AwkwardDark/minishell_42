/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 22:21:37 by pierre            #+#    #+#             */
/*   Updated: 2024/08/30 14:56:46 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_data	*data;
	char *input;

	argv = NULL;
	argc = 0;
	data = (t_data *)malloc(sizeof(t_data));
	data->env = ft_cpyenv(env);
	while((input = readline("prompt> ")) != 0) 
	{
		if (!ft_strcmp(input, "exit"))
			break ;
		else if (!ft_strncmp(input, "cd ", 2))
			ft_cd(&input[2]);
		else if (!ft_strncmp(input, "pwd", 3))
			ft_pwd();
		else if (!ft_strcmp(input, "env"))
			ft_env(data->env);
		else if (!ft_strncmp(input, "unset", 5))
		{
			if (input[5]) {
				ft_unset(&input[6], data);

			}
		}
		else if(!ft_strncmp(input, "export", 6))
		{
			char *key = (char *)malloc(sizeof(char) * 4);
			key[0]='N';
			key[1]='E';
			key[2]='W';
			key[3]='\0';
			char *val = (char *)malloc(sizeof(char) * 5);
			val[0]='Z';
			val[1]='I';
			val[2]='Z';
			val[3]='I';
			val[4]='\0';
			ft_export(&data->env, key, val);
		}
		else if (!ft_strcmp(input, "echo"))
		{
			printf("**********************\n");
			char *tab[5] = {"hello", "world", "I", "love", 0};
			ft_echo(tab, 1);
			printf("**********************\n");
			ft_echo(tab, 0);
			char *tab2[2] = {"hello", 0};
			printf("**********************\n");
			ft_echo(tab2, 0);
			printf("**********************\n");
			printf("**********************\n");
			ft_echo(tab2, 1);
		}
		free(input);
	}
	free(input);
	return 0;
}
