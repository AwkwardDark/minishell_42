/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:44:21 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/17 12:27:14 by pajimene         ###   ########.fr       */
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
