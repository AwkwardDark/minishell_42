/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 22:21:37 by pierre            #+#    #+#             */
/*   Updated: 2024/08/28 16:59:07 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int main(int argc, char **argv, char **env)
{
	t_data	*data;
	char *input;

	data = (t_data *)malloc(sizeof(t_data));
	data->env = env;
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
			if (input[5]) 
				ft_unset(&input[6], data);
		}
		free(input);
	}
	free(input);
	return 0;
}
