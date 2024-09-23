/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:42:11 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/23 12:43:20 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_error_message(char *path)
{
	if (!access(path, F_OK))
	{
		if (is_directory(path))
			return ("Is a directory");
		else
			return ("Permission denied");
	}
	return ("No such file or directory");
}
