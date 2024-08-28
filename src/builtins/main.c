/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 22:21:37 by pierre            #+#    #+#             */
/*   Updated: 2024/08/28 10:59:13 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int main(int argc, char **argv, char **env)
{
	char *input;

	while((input = readline("prompt> ")) != 0) 
	{
		if (!ft_strcmp(input, "exit"))
			break ;
		else if (!ft_strncmp(input, "cd ", 2))
			ft_cd(&input[2]);
		else if (!ft_strncmp(input, "pwd", 3))
			ft_pwd();
		else if (!ft_strcmp(input, "change"))

		free(input);
	}
	free(input);
	return 0;
}
