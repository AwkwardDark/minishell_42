/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 00:46:45 by pierre            #+#    #+#             */
/*   Updated: 2024/09/23 01:27:36 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(char *path)
{
	struct stat	mystat;

	if (stat(path, &mystat) != 0)
	{
		perror("Error getting file status");
		return (0);
	}
	if (S_ISDIR(mystat.st_mode))
		return (1);
	return (0);
}
