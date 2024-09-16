/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:44:21 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/17 01:44:12 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec(char *path, char **argv, char **env_arr)
{
	free(path);
	clear_wordar(argv);
	clear_wordar(env_arr);
	exit(EXIT_FAILURE);
}
