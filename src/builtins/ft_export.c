/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:43:01 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/01 11:24:05 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TODO In special parsing of the export check that the format 
	of export is right
	export key="value" => good
	export key=value => good
	export key = value => wrong
	and display error messages
*/

void	ft_export(t_env **env, char *key, char *value)
{
	t_env	*cur;

	cur = *env;
	if (!cur)
	{
		*env = ft_initenv(key, value);
		return ;
	}
	while (cur->next != NULL && ft_strcmp(cur->key, key))
		cur = cur->next;
	if (cur->next == NULL)
		cur->next = ft_initenv(key, value);
	else
		cur->value = value;
}
