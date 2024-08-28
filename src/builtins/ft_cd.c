/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:32:47 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/08/27 22:25:26 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* include "" */
// required includes to put in the .h
#include "builtin.h"

/* TODO
   needs the function ft_strtrim
   will not work properly if is given `cd..` cd 
   most be followed by a space */

void	ft_cd(char *path)
{
	char	*trimed_path;
	char	current[100];
	char	*home;

	trimed_path = ft_strtrim(path, " ");
	home = getenv("HOME");
	if (!ft_strcmp(trimed_path, ""))
	{
		if (home)
			chdir(home);
		else
			perror("minishell: cd");
	}
	else if (!opendir(trimed_path))
		perror("minishell: cd");
	else
		chdir(trimed_path);
	free(trimed_path);
}
