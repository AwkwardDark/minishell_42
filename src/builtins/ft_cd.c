/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:32:47 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/13 18:44:06 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TODO
   needs the function ft_strtrim
   will not work properly if is given `cd..` cd 
   most be followed by a space */

int	ft_cd(char *path, t_data *data)
{
	char	*home;

	home = getenv("HOME");
	if (!ft_strcmp(path, ""))
	{
		if (home)
			chdir(home);
		else
		{
			errorcmd_failed("cd", "HOME not set");
			return (1);
		}
	}
	else if (!opendir(path))
		perror("minishell: cd");
	else
		chdir(path);
	return (0);
}
